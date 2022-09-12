
#include "../top_down.h"
#define CREATE_AMOUNT 4
#define DAGGER_AMOUNT 800
#define	DAGGER_LIFE 292
#define DAGGER_HALF_X 32
#define DAGGER_HALF_Y 32
#define DAGGER_SPEED 16
#define TURN_SPEED 0.22

typedef struct	s_dfly
{
	t_vec		pos;
	t_vec		dir;
	t_vec		enem;
	int			target;
	int			turn_dir;	// 0 counter clockwise and 0 for clockwise
	int			active;
	int			crit;
}				t_dfly;

typedef struct	s_dagger
{
	uint8_t	tru;
	t_dfly	dagger[CREATE_AMOUNT];
	int		life;
}				t_dagger;

//simple init
void	init_daggers(t_dagger *dagger)
{
	int	i = 0, j;

	bzero(dagger, sizeof(t_dagger) * DAGGER_AMOUNT);
	while (i < DAGGER_AMOUNT)
	{
		j = 0;
		while (j < CREATE_AMOUNT)
		{
			dagger[i].dagger[j].active = 0;
			dagger[i].dagger[j].target = (-1);
			j++;
		}
		dagger[i].tru = 0;
		dagger[i].life = 0;
		i++;
	}
}

void	void_dagger(t_dagger *dagger, int curr)
{
	bzero(&dagger->dagger[curr], sizeof(t_dfly));
	dagger->dagger[curr].active = 0;
}

void	add_dir_to_dagger(t_dagger *dagger, int curr)
{
	switch (curr)
	{
		case 0:
			dagger->dagger[curr].dir.x = 0;
			dagger->dagger[curr].dir.y = (-1);
			break ;
		case 1:
			dagger->dagger[curr].dir.x = 1;
			dagger->dagger[curr].dir.y = 0;
			break ;
		case 2:
			dagger->dagger[curr].dir.x = 0;
			dagger->dagger[curr].dir.y = 1;
			break ;
		case 3:
			dagger->dagger[curr].dir.x = (-1);
			dagger->dagger[curr].dir.y = 0;
			break ;
	}
}

int	get_dagger_target(t_enemy *enem, t_dagger *dagger, int call_time)
{
	static int	index = 0;
	int			i_was = 0;
	int			i = 0;

	if (call_time == 0)
		index = 0;
	if (index > 0)
		i_was = 1;
	while (index < E_COUNT)
	{
		if (enem[index].type != 0)
		{
			if (place_meeting(enem[index].hbox, screen))
			{
				dagger->dagger[call_time].target = index;
				index++;
				return (0);
			}
		}
		index++;
	}
	if (i_was == 0)
	{
		dagger->tru = 0;
		return (1);
	}
	while (i < E_COUNT)
	{
		if (enem[i].type != 0)
		{
			if (place_meeting(enem[i].hbox, screen))
			{
				dagger->dagger[call_time].target = i;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	get_rotation_dir(t_enemy *enem, t_dagger *dagger, int curr)
{
	int	e = dagger->dagger[curr].target;
	int	enex = enem[e].text.rect.x + (enem[e].text.rect.w / 2);
	int	dagx = dagger->dagger[curr].pos.x + DAGGER_HALF_X;
	int	eney = enem[e].text.rect.y + (enem[e].text.rect.h / 2);
	int dagy = dagger->dagger[curr].pos.y + DAGGER_HALF_Y;

	switch (curr)
	{
		case 0:
			if (enex < dagx)
				dagger->dagger[curr].turn_dir = 0;
			else
				dagger->dagger[curr].turn_dir = 1;
			break ;
		case 1:
			if (eney < dagy)
				dagger->dagger[curr].turn_dir = 0;
			else
				dagger->dagger[curr].turn_dir = 1;
			break ;
		case 2:
			if (enex < dagx)
				dagger->dagger[curr].turn_dir = 1;
			else
				dagger->dagger[curr].turn_dir = 0;
			break ;
		case 3:
			if (eney < dagy)
				dagger->dagger[curr].turn_dir = 1;
			else
				dagger->dagger[curr].turn_dir = 0;
			break ;
	}
}

void	vec_to_enem_from_dagger(t_enemy *enem, t_dagger *dagger, int curr)
{
	int		e = dagger->dagger[curr].target;
	t_vec	vec;
	double	len;

	if (enem[e].type == 0)
		return ;
	vec.x = (dagger->dagger[curr].pos.x + DAGGER_HALF_X) - (enem[e].text.rect.x + (enem[e].text.rect.w / 2));
	vec.y = (dagger->dagger[curr].pos.y + DAGGER_HALF_Y) - (enem[e].text.rect.y + (enem[e].text.rect.h / 2));
	len = sqrt(vec.x * vec.x + vec.y * vec.y);
	dagger->dagger[curr].enem.x = vec.x / len;
	dagger->dagger[curr].enem.y = vec.y / len;
}

void	dagger_crit(t_dagger *dagger, int curr)
{
	if (insta_kill_active == 0)
	{
		dagger->dagger[curr].crit = 1;
		return ;
	}
	int	range = 17 - insta_kill_active;
	int	correct = 1;
	int	crit = 1;

	if (insta_kill_active != 0 && (rand() % range) == correct)
		crit = 2;
	dagger->dagger[curr].crit = crit;
}

void	add_values_do_dagger(t_enemy *enem, t_dagger *dagger, int curr)
{
	int	i = 0;
	int	bool = 0;

	dagger->tru = 1;
	dagger->life = DAGGER_LIFE;
	while (i < CREATE_AMOUNT)
	{
		if (i < dagger_active && bool == 0)
		{
			dagger->dagger[i].active = 1;
			dagger->dagger[i].pos.x = enem[curr].pos.x + (enem->text.rect.w / 2) - (DAGGER_HALF_X);
			dagger->dagger[i].pos.y = enem[curr].pos.y + (enem->text.rect.h / 2) - (DAGGER_HALF_Y);
			add_dir_to_dagger(dagger, i);
			if (get_dagger_target(enem, dagger, i))
			{
				bool = 1;
				void_dagger(dagger, i);
			}
			dagger_crit(dagger, i);
			get_rotation_dir(enem, dagger, i);
			vec_to_enem_from_dagger(enem, dagger, i);
		}
		else
			void_dagger(dagger, i);
		i++;
	}
}

void	create_dagger(t_enemy *enem, t_dagger *dagger, int curr)
{
	int	i = 0;

	while (dagger[i].tru == 1)
		i++;
	if (i < DAGGER_AMOUNT)
		add_values_do_dagger(enem, &dagger[i], curr);
}

void	check_dagger_life_and_maintain(t_dagger *dagger)
{
	dagger->life -= 1;
	if (dagger->dagger[0].active == 0 && dagger->dagger[1].active == 0
		&& dagger->dagger[2].active == 0 && dagger->dagger[3].active == 0)
		dagger->tru = 0;
	if (dagger->life <= 0)
		dagger->tru = 0;
	if (dagger->life == 12)
	{
		if (dagger->dagger[0].active == 1)
			dagger->dagger[0].active = 2;
		if (dagger->dagger[1].active == 1)
			dagger->dagger[1].active = 2;
		if (dagger->dagger[2].active == 1)
			dagger->dagger[2].active = 2;
		if (dagger->dagger[3].active == 1)
			dagger->dagger[3].active = 2;
	}
}

void	move_dagger(t_dagger *dagger, int i)
{
	double	len;

	dagger->dagger[i].dir.x += (dagger->dagger[i].enem.x * TURN_SPEED);
	dagger->dagger[i].dir.y += (dagger->dagger[i].enem.y * TURN_SPEED);
	len = sqrt(dagger->dagger[i].dir.x * dagger->dagger[i].dir.x + dagger->dagger[i].dir.y * dagger->dagger[i].dir.y);
	dagger->dagger[i].dir.x /= len;
	dagger->dagger[i].dir.y /= len;
	dagger->dagger[i].pos.x -= (dagger->dagger[i].dir.x * DAGGER_SPEED);
	dagger->dagger[i].pos.y -= (dagger->dagger[i].dir.y * DAGGER_SPEED);
}

void	dagger_to_enemy_hit(t_enemy *enem, t_dagger *dagger, int i, t_audio *audio)
{
	int	e = dagger->dagger[i].target;
	int	x = dagger->dagger[i].pos.x + DAGGER_HALF_X;
	int	y = dagger->dagger[i].pos.y + DAGGER_HALF_Y;

	if (point_meeting(x, y, enem[e].hbox) && enem[e].type != 0)
	{
		dagger->dagger[i].active += 1;
		enem[e].got_hit = 5;
		enem[e].hp -= (bullet_damage * dagger->dagger[i].crit);
		Mix_PlayChannel(4, audio->hit, 0);
		if (dagger->dagger[i].crit == 2)
			Mix_PlayChannel(17, critical_hit_soundeffect, 0);
		shock_the_enemies(enem, NULL, NULL, e, 1);
		if (enem[e].hp <= 0)
		{
			enem_kill_counter(&enem[e]);
			orb_main(enem, NULL, NULL, NULL, e);
			particle_main(&enem[e], NULL, NULL, e);
			enem[e].type = 0;
			Mix_PlayChannel(2, audio->enem_death[0], 0);
			dead_whale_explosion_main(enem, e, NULL, 0, NULL, NULL);
			dagger_main(enem, e, NULL, NULL, NULL);
			if (s_shake_active != 2)
				s_shake_active = 1;
			screen_shake_amount = 1;
		}
	}
}

static int	get_the_vec_angle(t_vec dir, double *rad)
{
	t_vec	up = {0, 1};
	int		ang;

	*rad = calc_a(dir, up);
	ang = degree(*rad);
	return (ang);
}

void	manage_dagger_target(t_enemy *enem, t_dagger *dagger, int curr)
{
	int	e = dagger->dagger[curr].target;
	int	i = 0;

	if (enem[e].type == 0)
	{
		while (i < E_COUNT)
		{
			if (enem[i].type != 0 && place_meeting(enem[i].hbox, screen))
			{
				dagger->dagger[curr].target = i;
				return ;
			}
			i++;
		}
	}
	dagger->dagger[curr].active = 2;
}

void	draw_dagger(t_dagger *dagger, t_graphics *all, t_textures *text, int curr, int fx)
{
	SDL_Rect	dest = {0, 0, 64, 64};
	SDL_Rect	frame = {0, 0, 64, 64};
	SDL_Point	rot = {32, 32};
	int			ang;
	double		rad;

	frame.x = 64 * fx;
	dest.x = dagger->dagger[curr].pos.x;
	dest.y = dagger->dagger[curr].pos.y;
	ang = get_the_vec_angle(dagger->dagger[curr].dir, &rad);
	if (dagger->dagger[curr].dir.x > 0)
		ang *= (-1);
	if (place_meeting(dest, screen))
	{
		screen_shaker(&dest.x, &dest.y);
		if (dagger->dagger[curr].crit == 1)
			make_curr_graph(all, text->dagger, &dest, &frame, &rot, ang, 0);
		else
			make_curr_graph(all, text->dagger_crit, &dest, &frame, &rot, ang, 0);
	}
}

//main function for iterating the dagger array
//do the target change if the current target dies
void	dagger_seek(t_enemy *enem, t_dagger *dagger, t_graphics *all, t_textures *text, t_audio *audio)
{
	int		i = 0, j;

	while (i < E_COUNT)
	{
		j = 0;
		if (dagger[i].tru == 1)
		{
			if (dagger[i].life == DAGGER_LIFE)
				Mix_PlayChannel(16, audio->dagger_woosh, 0);
			while (j < CREATE_AMOUNT)
			{
				if (dagger[i].dagger[j].active == 1)
				{
					move_dest_from_player(&dagger[i].dagger[j].pos);
					vec_to_enem_from_dagger(enem, &dagger[i], j);
					move_dagger(&dagger[i], j);
					dagger_to_enemy_hit(enem, &dagger[i], j, audio);
					draw_dagger(&dagger[i], all, text, j, 0);
				}
				else if (dagger[i].dagger[j].active > 1)
				{
					move_dest_from_player(&dagger[i].dagger[j].pos);
					draw_dagger(&dagger[i], all, text, j, ((dagger[i].dagger[j].active - 1)) / 2);
					dagger[i].dagger[j].active += 1;
					if (dagger[i].dagger[j].active == 12)
						dagger[i].dagger[j].active = 0;
				}
				j++;
			}
			check_dagger_life_and_maintain(&dagger[i]);
		}
		i++;
	}
}

//the main function for the dagger upgrade
void	dagger_main(t_enemy *enem, int sign, t_graphics *all, t_textures *text, t_audio *audio)
{
	static t_dagger	dagger[DAGGER_AMOUNT];

	if (sign == START_INIT)
		return (init_daggers(dagger));
	if (dagger_active == 0)
		return ;
	if (sign >= 0)
		return (create_dagger(enem, dagger, sign));
	dagger_seek(enem, dagger, all, text, audio);
}
