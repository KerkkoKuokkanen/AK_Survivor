
#include "../top_down.h"

void	p_hit(double len, SDL_Rect hbox, int type, t_enemy *enem)
{
	uint8_t	bool = 0;

	if (len < 50)
	{
		if (place_meeting(phbox, hbox))
		{
			player_hit = 1;
			bool = 1;
		}
	}
	else if (type == 4)
	{
		if (place_meeting(phbox, hbox))
		{
			player_hit = 1;
			bool = 1;
		}
	}
	if (bool == 1 && (enem->type == 3 || enem->type == 4))
		enem->enem_speed = 3;
}

void	print_health(t_tex heart, t_graphics *all, int i, int sign)
{
	SDL_Rect	dest;

	dest.y = 10;
	dest.w = 32;
	dest.h = 32;
	dest.x = 10 + (40 * i);
	if (sign == 1)
		make_curr_graph(all, heart, &dest, &full_heart, NULL, 0, 0);
	else
		make_curr_graph(all, heart, &dest, &empty_heart, NULL, 0, 0);
}

void	if_hit(int *healt_index, int *health, int *recovery)
{
	*health = 0;
	*healt_index -= 1;
	*recovery = 90;
	player_hit = 0;
}

int	health_main(t_tex *heart, t_graphics *all, Mix_Chunk **hurt, int sign)
{
	static int	healt_index = 2;
	static int	health[3] = {1, 1, 1};
	static int	recovery = 0;
	int			i = 0;

	if (sign == START_INIT)
	{
		healt_index = 2;
		health[0] = 1; health[1] = 1; health[2] = 1;
		recovery = 0;
		return (0);
	}
	if (sign == 4)
	{
		healt_index += 1;
		health[healt_index] = 1;
		return (0);
	}
	else if (sign == 3)
		return (healt_index);
	speed = real_speed;
	if (recovery > 0)
		recovery--;
	if (player_hit == 1 && rage_now <= 0)
	{
		speed = real_speed / 2;
		player_hit = 0;
		if (healt_index >= 0 && recovery == 0)
		{
			s_shake_active = 2;
			pl_hit_anim = 1;
			if_hit(&healt_index, &health[healt_index], &recovery);
			if (healt_index == (-1))
				return (DEATH_OF_PLAYER);
			Mix_PlayChannel(3, hurt[rand() % 2], 0);
		}
	}
	if (rage_now > 0 && player_hit == 1)
		player_hit = 0;
	while (i < 3)
	{
		print_health(*heart, all, i, health[i]);
		i++;
	}
	return (0);
}
