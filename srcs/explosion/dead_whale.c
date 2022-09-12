
#include "../top_down.h"
#define EXPLOSION_COUNT 800
#define EXP_HBOX_X 90
#define EXP_HBOX_Y 90
#define EXP_HBOX_X_HALF 64
#define EXP_HBOX_Y_HALF 64
#define EXP_LIFE 44 //this is the amount of sprites in the sheet times two
#define EXP_HITBOX_ACTIVE 28

typedef struct	s_dead_whale
{
	t_vec		pos;
	int			life;
	SDL_Rect	hbox;
	uint8_t		tru;
}				t_dead_whale;

// first inits struct
void	init_dead_whale(t_dead_whale *exp)
{
	int	i = 0;

	bzero(exp, sizeof(t_dead_whale) * EXPLOSION_COUNT);
	while (i < EXPLOSION_COUNT)
	{
		exp[i].tru = 0;
		exp[i].life = 0;
		exp[i].hbox.w = EXP_HBOX_X;
		exp[i].hbox.h = EXP_HBOX_Y;
		i++;
	}
}

//init values for new explosion
void	assign_values_to_exp(t_enemy *enem, t_dead_whale *exp)
{
	exp->tru = 1;
	exp->life = EXP_LIFE;
	exp->pos.x = enem->pos.x + (enem->text.rect.w / 2) - (EXP_HBOX_X_HALF);
	exp->pos.y = enem->pos.y + (enem->text.rect.h / 2) - (EXP_HBOX_Y_HALF);
	exp->hbox.x = exp->pos.x + 20;
	exp->hbox.y = exp->pos.y + 20;
}

//creates the explosion on a free spot on the struct
void	create_explosion(t_enemy *enem, t_dead_whale *exp, int curr)
{
	int	i = 0;

	while (i < EXPLOSION_COUNT)
	{
		if (exp[i].tru == 0)
			break ;
		i++;
	}
	if (i < EXPLOSION_COUNT)
		assign_values_to_exp(&enem[curr], &exp[i]);
}

void	make_explosion_sound(int life, t_audio *audio)
{
	if (life == EXP_LIFE)
		Mix_PlayChannel(15, audio->dead_whale, 0);
}

//mange life of the exp
void	manage_exp_life(t_dead_whale *exp)
{
	exp->life -= 1;
	if (exp->life <= 0)
	{
		exp->tru = 0;
		exp->life = 0;
	}
}

int	get_the_x_for_exp_frame(int life)
{
	return (64 * (44 - life));
}

void	update_exp_hbox(t_dead_whale *exp)
{
	exp->hbox.x = exp->pos.x + 20;
	exp->hbox.y = exp->pos.y + 20;
}

int	get_explosion_damage()
{
	return (bullet_damage * dead_whale_active);
}

//explosion hitbox check for the enemies
//and if hit doing the correct things
void	exp_hitting_enem(t_enemy *enem, t_dead_whale *exp, t_audio *audio)
{
	if (exp->life != 30)
		return ;
	int	i = 0;
	while (i < E_COUNT)
	{
		if (enem[i].type != 0)
		{
			if (place_meeting(exp->hbox, enem[i].hbox))
			{
				enem[i].got_hit = 5;
				enem[i].hp -= get_explosion_damage();
				Mix_PlayChannel(4, audio->hit, 0);
				if (enem[i].hp <= 0)
				{
					enem_kill_counter(&enem[i]);
					orb_main(enem, NULL, NULL, NULL, i);
					particle_main(&enem[i], NULL, NULL, i);
					enem[i].type = 0;
					Mix_PlayChannel(2, audio->enem_death[0], 0);
					dead_whale_explosion_main(enem, i, NULL, 0, NULL, NULL);
					dagger_main(enem, i, NULL, NULL, NULL);
					if (s_shake_active != 2)
						s_shake_active = 1;
					screen_shake_amount = 1;
				}
			}
		}
		i++;
	}
}

//audio channel 15
//iters the struct for the dead whale explosion
void	iter_explosion(t_enemy *enem, t_dead_whale *exp, t_graphics *all, t_tex *explosion, t_audio *audio)
{
	int			i = 0;
	SDL_Rect	dest = {0, 0, 128, 128};
	SDL_Rect	frame = {0, 0, 64, 64};

	while (i < EXPLOSION_COUNT)
	{
		if (exp[i].tru == 1)
		{
			make_explosion_sound(exp[i].life, audio);
			move_dest_from_player(&exp[i].pos);
			update_exp_hbox(&exp[i]);
			dest.x = exp[i].pos.x;
			dest.y = exp[i].pos.y;
			frame.x = get_the_x_for_exp_frame(exp[i].life);
			exp_hitting_enem(enem, &exp[i], audio);
			screen_shaker(&dest.x, &dest.y);
			if (place_meeting(exp[i].hbox, screen))
				make_curr_graph(all, *explosion, &dest, &frame, NULL, 0, 0);
			manage_exp_life(&exp[i]);
		}
		i++;
	}
}

//The main function for the dead whale perk handling
void	dead_whale_explosion_main(t_enemy *enem, int curr, t_graphics *all, int sign, t_audio *audio, t_tex *explosion)
{
	static t_dead_whale	exp[EXPLOSION_COUNT];

	if (sign == START_INIT)
		return (init_dead_whale(exp));
	if (dead_whale_active == 0)
		return ;
	if (sign == 0)
		return (create_explosion(enem, exp, curr));
	iter_explosion(enem, exp, all, explosion, audio);
}
