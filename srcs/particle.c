
#include "top_down.h"
# define BOSS_PARTICLE_AMOUNT 250
# define BOSS_BLOOD_LIFE 50

typedef struct	s_boss_spatter
{
	uint8_t		tru;
	int			life_time;
	t_vec		starting_pos;
	t_particle	blood[BOSS_PARTICLE_AMOUNT];
}				t_boss_spatter;

void	put_particles_to_screen(t_vec pos, t_tex blood, t_graphics *all)
{
	particle_srect.x = rand() % 27;
	particle_dest.x = pos.x;
	particle_dest.y = pos.y;
	if (place_meeting(particle_dest, screen))
		make_curr_graph(all, blood, &particle_dest, &particle_srect, NULL, 0, 0);
}

void	put_boss_particles_to_screen(t_vec pos, t_tex blood, t_graphics *all)
{
	particle_srect.x = rand() % 27;
	boss_particle_dest.x = pos.x;
	boss_particle_dest.y = pos.y;
	if (place_meeting(boss_particle_dest, screen))
		make_curr_graph(all, blood, &boss_particle_dest, &particle_srect, NULL, 0, 0);
}


void	move_particle_dir(t_particle *blood)
{
	blood->pos.x += blood->dir.x;
	blood->pos.y += blood->dir.y;
	blood->dir.y += 0.5;
}

void	move_boss_particle_dir(t_particle *blood)
{
	blood->pos.x += blood->dir.x;
	blood->pos.y += blood->dir.y;
	blood->dir.y += 0.3;
}

void	create_directions(t_vec starting_pos, t_particle *particles)
{
	int		i = 0;
	float	rad;

	while (i < PARTICLE_AMOUNT)
	{
		rad = float_rand();
		particles[i].pos = starting_pos;
		particles[i].dir.x = (cos(rad) * float_rand() * 2.f);
		particles[i].dir.y = (sin(rad) * float_rand() * 2.f);
		i++;
	}
}

void	create_boss_particle_directions(t_vec starting_pos, t_particle *particles)
{
	int		i = 0;
	float	rad;

	while (i < BOSS_PARTICLE_AMOUNT)
	{
		rad = float_rand();
		particles[i].pos = starting_pos;
		particles[i].dir.x = (cos(rad) * float_rand() * 2.f);
		particles[i].dir.y = (sin(rad) * float_rand() * 2.f);
		i++;
	}
}


static void	init_boss_particles(t_boss_spatter *bloods)
{
	int	i = 0;
	int	j;

	bzero(bloods, sizeof(t_boss_spatter) * 20);
	while (i < 20)
	{
		bloods[i].tru = 0;
		bloods[i].life_time = 0;
		j = 0;
		while (j < BOSS_PARTICLE_AMOUNT)
		{
			bloods[i].blood[j].dest.h = 3;
			bloods[i].blood[j].dest.w = 3;
			j++;
		}
		i++;
	}
}

void	create_boss_particle(t_enemy *enem, int curr_e, t_boss_spatter *bloods)
{
	int	i = 0;

	while (i < 20)
	{
		if (bloods[i].tru == 0)
		{
			bloods[i].tru = 1;
			bloods[i].starting_pos.x = enem->hbox.x + (enem->hbox.w / 2);
			bloods[i].starting_pos.y = enem->hbox.y + (enem->hbox.h / 2);
			create_boss_particle_directions(bloods[i].starting_pos, bloods[i].blood);
			return ;
		}
		i++;
	}
}

void	check_life_time_of_boss_particle(t_boss_spatter *blood)
{
	blood->life_time += 1;
	if (blood->life_time == BOSS_BLOOD_LIFE)
	{
		blood->tru = 0;
		blood->life_time = 0;
	}
}

void	animate_boss_particles(t_boss_spatter *bloods, t_tex blood, t_graphics *all)
{
	int	x, y = 0;

	while (y < 20)
	{
		if (bloods[y].tru == 1)
		{
			x = 0;
			while (x < BOSS_PARTICLE_AMOUNT)
			{
				move_dest_from_player(&bloods[y].blood[x].pos);
				move_boss_particle_dir(&bloods[y].blood[x]);
				put_boss_particles_to_screen(bloods[y].blood[x].pos, blood, all);
				x++;
			}
			check_life_time_of_boss_particle(&bloods[y]);
		}
		y++;
	}
}

void	boss_particle(t_enemy *enem, t_tex *blood, t_graphics *all, int sign)
{
	static t_boss_spatter	boss_splatter[20];

	if (sign == START_INIT)
		return (init_boss_particles(boss_splatter));
	if (sign != (-1))
	{
		create_boss_particle(enem, sign, boss_splatter);
		return ;
	}
	animate_boss_particles(boss_splatter, *blood, all);
}

static void	init_particles(t_blood_spatter *bloods)
{
	int	i = 0;
	int	j;

	boss_particle(NULL, NULL, NULL, START_INIT);
	bzero(bloods, sizeof(t_blood_spatter) * E_COUNT);
	while (i < E_COUNT)
	{
		bloods[i].tru = 0;
		bloods[i].life_time = 0;
		j = 0;
		while (j < PARTICLE_AMOUNT)
		{
			bloods[i].blood[j].dest.h = 3;
			bloods[i].blood[j].dest.w = 3;
			j++;
		}
		i++;
	}
}

static void	create_blood_particle_start(t_enemy *enem, int curr_e, t_blood_spatter *bloods)
{
	int	i = 0;

	while (i < E_COUNT)
	{
		if (bloods[i].tru == 0)
		{
			bloods[i].tru = 1;
			bloods[i].starting_pos.x = enem->hbox.x + (enem->hbox.w / 2);
			bloods[i].starting_pos.y = enem->hbox.y + (enem->hbox.h / 2);
			create_directions(bloods[i].starting_pos, bloods[i].blood);
			return ;
		}
		i++;
	}
}

void	check_life_time_of_particle(t_blood_spatter *blood)
{
	blood->life_time += 1;
	if (blood->life_time >= normal_particle_blood_life)
	{
		blood->tru = 0;
		blood->life_time = 0;
	}
}

void	animate_particles(t_blood_spatter *bloods, t_tex blood, t_graphics *all)
{
	int	x, y = 0;

	while (y < E_COUNT)
	{
		if (bloods[y].tru == 1)
		{
			x = 0;
			while (x < PARTICLE_AMOUNT)
			{
				move_dest_from_player(&bloods[y].blood[x].pos);
				move_particle_dir(&bloods[y].blood[x]);
				put_particles_to_screen(bloods[y].blood[x].pos, blood, all);
				x++;
			}
			check_life_time_of_particle(&bloods[y]);
		}
		y++;
	}
}

void	particle_main(t_enemy *enem, t_tex *blood, t_graphics *all, int sign)
{
	static t_blood_spatter	bloods[E_COUNT];

	if (sign == START_INIT)
		return (init_particles(bloods));
	if (sign != (-1))
	{
		if (enem->type == 4)
			boss_particle(enem, NULL, NULL, sign);
		else
			create_blood_particle_start(enem, sign, bloods);
		return ;
	}
	animate_particles(bloods, *blood, all);
}
