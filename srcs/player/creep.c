
#include "../top_down.h"
#define CREEP_AMOUNT 130
#define CREEP_HBOX_X 32
#define CREEP_HBOX_Y 32
#define CREEP_X 620
#define CREEP_Y 420
#define	CREEP_TIME 8

int	creep_life = 240;

typedef struct	s_creep
{
	t_vec		pos;
	SDL_Rect	hbox;
	int			life;
	int			size_bonus;
	uint8_t		tru;
}				t_creep;

//init
void	init_creep(t_creep *creep)
{
	int	i = 0;

	bzero(creep, sizeof(t_creep) * CREEP_AMOUNT);
	while (i < CREEP_AMOUNT)
	{
		creep[i].tru = 0;
		creep[i].hbox.w = CREEP_HBOX_X;
		creep[i].hbox.h = CREEP_HBOX_Y;
		creep[i].size_bonus = 0;
		i++;
	}
}

//create single creep
void	assing_values_to_new_creep(t_creep *creep)
{
	creep->pos.x = CREEP_X + (rand() % 11) - 5;
	creep->pos.y = CREEP_Y + (rand() % 11) - 5;
	creep->tru = 1;
	creep->life = creep_life;
	creep->hbox.x = creep->pos.x;
	creep->hbox.y = creep->pos.y;
	creep->size_bonus = rand() % 6 - 2;
}

//responsible for the right time to create the individual creep
void	create_creep(t_creep *creep)
{
	int			i = 0;
	static int	creep_now = 0;
	int			can_creep = 0;

	creep_now++;
	if (creep_now == 4)
	{
		can_creep = 1;
		creep_now = 0;
	}
	if (can_creep == 0)
		return ;
	while (i < CREEP_AMOUNT)
	{
		if (creep[i].tru == 0)
			break ;
		i++;
	}
	if (i < CREEP_AMOUNT)
		assing_values_to_new_creep(&creep[i]);
}

//manages creep.life variable
int	manage_creep_life(t_creep *creep)
{
	creep->life -= 1;
	if (creep->life <= 0)
		creep->tru = 0;
	if (creep->life < 12)
		return (32 * (6 - (creep->life / 2) + 1));
	return (0);
}

void	update_creep_hbox(t_creep *creep)
{
	creep->hbox.x = creep->pos.x;
	creep->hbox.y = creep->pos.y;
}

//get dmg
int	creep_dmg_num(void)
{
	if (creep_active == 1)
		return (bullet_damage / 10);
	if (creep_active == 5)
		return (bullet_damage * 1.3);
	return (bullet_damage / (10 - creep_active));
}

//function makes the enemy hbox temporally smaller so it looks more natural with the creep mechanic
SDL_Rect	make_creep_box(t_enemy *enem)
{
	SDL_Rect	creep_box;
	int			sub;

	sub = (enem->hbox.h + enem->hbox.y) - enem->hbox.y;
	sub *= 0.8;
	creep_box.w = enem->hbox.w;
	creep_box.x = enem->hbox.x;
	creep_box.y = enem->hbox.y + sub;
	creep_box.h = enem->hbox.h - sub;
	return (creep_box);
}

//creep and enem check
void	check_if_creep_hit_enem(t_creep *creep, t_enemy *enem, t_audio *audio)
{
	int			i = 0;

	while (i < E_COUNT)
	{
		if (enem[i].type != 0)
		{
			if (place_meeting(make_creep_box(&enem[i]), creep->hbox))
			{
				Mix_PlayChannel(14, audio->acid, 0);
				enem[i].got_hit = 5;
				enem[i].hp -= creep_dmg_num();
				if (enem[i].hp <= 0)
				{
					enem_kill_counter(&enem[i]);
					orb_main(enem, NULL, NULL, NULL, i);
					particle_main(&enem[i], NULL, NULL, i);
					Mix_PlayChannel(2, audio->enem_death[0], 0);
					dead_whale_explosion_main(enem, i, NULL, 0, NULL, NULL);
					dagger_main(enem, i, NULL, NULL, NULL);
					if (s_shake_active != 2)
						s_shake_active = 1;
					screen_shake_amount = 1;
					enem[i].type = 0;
				}
			}
		}
		i++;
	}
}

//manages the different creep sizes
void	manage_creep_dest(SDL_Rect *dest, int size_bonus)
{
	dest->x -= size_bonus;
	dest->w += (size_bonus + size_bonus);
	dest->y -= size_bonus;
	dest->h += (size_bonus + size_bonus);
}

//function to iter the creep array and call all the nessesary funtions
void	iter_creep_array(t_creep *creep, t_enemy *enem, t_graphics *all, t_audio *audio)
{
	int			i = 0;
	static int	creep_hit_delay = 0;
	SDL_Rect	dest = {0, 0, 32, 32};
	SDL_Rect	frame = {0, 0, 32, 32};

	while (i < CREEP_AMOUNT)
	{
		if (creep[i].tru == 1)
		{
			move_dest_from_player(&creep[i].pos);
			dest.x = creep[i].pos.x;
			dest.y = creep[i].pos.y;
			frame.x = manage_creep_life(&creep[i]);
			manage_creep_dest(&dest, creep[i].size_bonus);
			update_creep_hbox(&creep[i]);
			if (creep_hit_delay == CREEP_TIME)
				check_if_creep_hit_enem(&creep[i], enem, audio);
			make_curr_graph(all, creep_upgrade_texture, &dest, &frame, NULL, 0, 0);
		}
		dest.w = 32;
		dest.h = 32;
		i++;
	}
	if (creep_hit_delay == CREEP_TIME)
		creep_hit_delay = 0;
	creep_hit_delay++;
}

//main function for the creep game mechanic
void	creep_main(t_enemy *enem, t_graphics *all, t_audio *audio)
{
	static t_creep	creep[CREEP_AMOUNT];

	if (all == NULL)
		return (init_creep(creep));
	if (creep_active == 0)
		return ;
	create_creep(creep);
	iter_creep_array(creep, enem, all, audio);
}
