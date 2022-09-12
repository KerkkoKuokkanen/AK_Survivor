
#include "../top_down.h"
#define EGG_SIZE 64
#define EGG_HBOX_X 50
#define EGG_HBOX_Y 60 
#define EGG_HITS 20
#define EGG_DISTANCE 5000
#define EGG_PART_AMOUNT 6
#define EGG_LIFE 20

typedef struct	s_egg_shatter
{
	t_vec		dir[EGG_PART_AMOUNT];
	t_vec		pos[EGG_PART_AMOUNT];
	int			lifetime;
	uint8_t		tru;
}				t_egg_shatter;

void	activate_egg(t_egg *egg, int *egg_active)
{
	float	random;
	int		j = 0, i = rand() % 10 + 1;

	while (j < i)
	{
		random = float_rand();
		j++;
	}
	*egg_active = 1;
	egg->got_hit = 0;
	egg->frame.x = 0;
	egg->frame.y = 0;
	egg->frame.w = 64;
	egg->frame.h = 64;
	egg->dest.x = (cos(random) * egg_dist_value) + CENTER_X;
	egg->dest.y = (sin(random) * egg_dist_value) + CENTER_Y;
	egg->hbox.x = egg->dest.x + 15;
	egg->hbox.y = egg->dest.y + 10;
	egg->hbox.w = EGG_HBOX_X;
	egg->hbox.h = EGG_HBOX_Y;
	egg->hits = EGG_HITS;
}

void	init_egg_shatter(t_egg_shatter *part, uint8_t *bool)
{
	*bool = 1;
	bzero(part, sizeof(t_egg_shatter));
	part->tru = 0;
	part->lifetime = 0;
}

void	eggshells_start(t_egg *egg, t_egg_shatter *part, t_vec start_pos)
{
	int		i = 0;
	float	rad;

	part->tru = 1;
	part->lifetime = EGG_LIFE;
	while (i < EGG_PART_AMOUNT)
	{
		rad = float_rand();
		part->pos[i] = start_pos;
		part->dir[i].x = (cos(rad) * float_rand() * 2.f);
		part->dir[i].y = (sin(rad) * float_rand() * 2.f);
		i++;
	}
}

void	move_eggshell(t_egg_shatter *part)
{
	int	i = 0;

	while (i < EGG_PART_AMOUNT)
	{
		part->pos[i].x += part->dir[i].x;
		part->pos[i].y += part->dir[i].y;
		part->dir[i].y += 0.5;
		i++;
	}
}

void	shells_to_screen(t_egg_shatter *part, t_graphics *all)
{
	int			i = 0;
	static int	shell_angle[6] = {0, 60, 120, 180, 240, 300};
	SDL_Rect	shell_dest = {0 ,0 ,16, 16};
	SDL_Point	shell_point = {8, 8};

	while (i < EGG_PART_AMOUNT)
	{
		if (shell_angle[i] >= 360)
			shell_angle[i] = 0;
		i++;
	}
	i = 0;
	while (i < EGG_PART_AMOUNT)
	{
		shell_angle[i] += 10;
		move_dest_from_player(&part->pos[i]);
		shell_dest.x = part->pos[i].x;
		shell_dest.y = part->pos[i].y;
		make_curr_graph(all, eggshell_tex, &shell_dest, NULL, &shell_point, shell_angle[i], 0);
		if (shell_angle[i] >= 360)
			shell_angle[i] -= 360;
		i++;
	}
}

void	eggshell_life(t_egg_shatter *part)
{
	part->lifetime -= 1;
	if (part->lifetime <= 0)
		part->tru = 0;
}

void	egg_shatter(t_egg *egg, t_graphics *all, int call_from)
{
	static t_egg_shatter	particles;
	static uint8_t			bool = 0;
	t_vec					start;

	if (bool == 0 || call_from == START_INIT)
		init_egg_shatter(&particles, &bool);
	if (call_from == 1)
	{
		start.x = egg->dest.x;
		start.y = egg->dest.y;
		return (eggshells_start(egg, &particles, start));
	}
	if (particles.tru == 1)
	{
		move_eggshell(&particles);
		shells_to_screen(&particles, all);
		eggshell_life(&particles);
	}
}

void	egg_hit(t_bullets *bullets, t_egg *egg, int *egg_active, t_graphics *all)
{
	int	i = 0;

	while (i < BULLET_COUNT)
	{
		if (bullets[i].tru == 1)
		{
			if (place_meeting(bullets[i].hbox, egg->hbox))
			{
				Mix_PlayChannel(4, hit_soundeffect, 0);
				bullets[i].tru = 0;
				egg->got_hit = 5;
				egg->hits -= 1;
				if (egg->hits <= 0)
				{
					Mix_PlayChannel(13, egg_crack, 0);
					egg->dest.x += 24;
					egg->dest.y += 24;
					*egg_active = 2;
					egg_shatter(egg, all, 1);
				}
			}
		}
		i++;
	}
}

void	animate_egg(t_egg *egg)
{
	static int	up_down = 0;
	int			egg_hitter = EGG_HITS - egg->hits;
	SDL_Rect	dest;
	t_tex		curr_egg_text;

	if (up_down == 94)
		up_down = 0;
	egg->frame.x = 64 * (egg_hitter / 4);
	move_dest_from_player(&egg->dest);
	dest.y = egg->dest.y + get_frame_multi(up_down);
	dest.x = egg->dest.x;
	dest.w = EGG_SIZE;
	dest.h = EGG_SIZE;
	egg->hbox.x = dest.x;
	egg->hbox.y = dest.y;
	screen_shaker(&dest.x, &dest.y);
	if (egg->got_hit > 0)
	{
		egg->got_hit -= 1;
		curr_egg_text = egg_hit_full_texture;
	}
	else
		curr_egg_text = egg_full_texture;
	if (place_meeting(dest, screen))
		ysort(NULL, curr_egg_text, &dest, &egg->frame, NULL, 0, 0, 0);
	up_down += 1;
}

void	move_egg_orb(t_egg *egg, int *om_orb, int *egg_active)
{
	t_vec	dir;
	double	len;

	dir.x = egg->dest.x - CENTER_X;
	dir.y = egg->dest.y - CENTER_Y;
	len = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x = dir.x / len;
	dir.y = dir.y / len;
	if (len < 15)
	{
		Mix_PlayChannel(6, coin_soundeffect, 0);
		egg_lvl_up_time = 1;
		*egg_active = 3;
		*om_orb = 0;
	}
	egg->dest.x -= dir.x * 7;
	egg->dest.y -= dir.y * 7;
}

void	egg_orb(t_egg *egg, t_graphics *all, int *egg_active, int sign)
{
	SDL_Rect	dest = {0, 0, 16, 16};
	static int	om_orb = 0;

	if (sign == START_INIT)
	{
		om_orb = 0;
		return ;
	}
	move_dest_from_player(&egg->dest);
	dest.x = egg->dest.x;
	dest.y = egg->dest.y;
	egg->hbox.x = dest.x;
	egg->hbox.y = dest.y;
	screen_shaker(&dest.x, &dest.y);
	if ((place_meeting(big_phbox, dest) && *egg_active == 2) || om_orb == 1)
	{
		om_orb = 1;
		move_egg_orb(egg, &om_orb, egg_active);
	}
	if (place_meeting(dest, screen) && *egg_active == 2)
		make_curr_graph(all, white_orb, &dest, NULL, NULL, 0, 0);
}

void	egg_cooldown_time(int *egg_active)
{
	static int	egg_cooldown = 0;

	if (*egg_active == 3)
	{
		*egg_active = 4;
		egg_cooldown = 180;
	}
	egg_cooldown--;
	if (egg_cooldown <= 0)
		*egg_active = 0;
}

void	can_arrow_point(t_egg *egg, int egg_active)
{
	can_arrow = 0;
	if (egg_active == 1 || egg_active == 2)
	{
		if (!place_meeting(egg->hbox, screen))
			can_arrow = 1;
	}
}

t_vec	*egg_init_func(int *egg_active, int *egg_amount, t_egg *egg)
{
	*egg_active = 0;
	*egg_amount = 0;
	bzero(egg, sizeof(t_egg));
	egg_orb(NULL, NULL, NULL, START_INIT);
	return (NULL);
}

t_vec	*egg_main(t_bullets *bullets, t_graphics *all, int sign)
{
	static int		egg_active = 0;
	static int		egg_amount = 0;
	static t_egg	egg;

	if (sign == START_INIT)
		return (egg_init_func(&egg_active, &egg_amount, &egg));
	can_arrow_point(&egg, egg_active);
	if (egg_active == 0 && egg_amount != 14)
	{
		activate_egg(&egg, &egg_active);
		egg_amount += 1;
		if (egg_amount > 7)
			egg_dist_value = 6000;
		if (egg_amount > 9)
			egg_dist_value = 7500;
	}
	if (sign == 2)
		return (&egg.dest);
	if (sign == 1)
	{
		if (egg_active == 1)
			egg_hit(bullets, &egg, &egg_active, all);
		return (NULL);
	}
	if (egg_active == 1)
		animate_egg(&egg);
	else if (egg_active == 2)
		egg_orb(&egg, all, &egg_active, sign);
	else if (egg_active >= 3)
		egg_cooldown_time(&egg_active);
	egg_shatter(&egg, all, 0);
	return (NULL);
}
