
#include "../top_down.h"
int	curr_boss;

typedef struct	s_bosses_penta
{
	int			boss_spawn;
	int			health;
	int			boss_lifetime;
	SDL_Rect	dest;
}				t_bosses_penta;

void	init_struct(t_bosses_penta *pentas)
{
	int i = 0;

	curr_boss = 0;
	bzero(pentas, sizeof(t_bosses_penta) * 20);
	while (i < 20)
	{
		pentas[i].boss_spawn = (-1);
		pentas[i].health = (-1);
		i++;
	}
}

int	get_frame_multi(int frame_multi)
{
	double	f = frame_multi;
	double	ret = ((sin(f / 15 - 1.5) * 10) + 10);
	return (ret);
}

int		get_boss_original_health()
{
	if (curr_boss > 15)
		return (1500000);
	if (curr_boss > 10)
		return (908000);
	if (curr_boss > 5)
		return (300000);
	return (96000);
}

void	penta_creator(t_bosses_penta *pentas, Mix_Chunk *clang, int sign, int boss_lifetime)
{
	int	i = 0;

	while (i < 20)
	{
		if (pentas[i].boss_spawn == (-1))
		{
			Mix_PlayChannel(10, clang, 2);
			pentas[i].boss_spawn = 0;
			pentas[i].dest.x = P_POS_X - 160;
			pentas[i].dest.y = P_POS_Y - 115;
			pentas[i].dest.w = 360;
			pentas[i].dest.h = 360;
			pentas[i].health = get_boss_original_health();
			pentas[i].boss_lifetime = 0;
			if (sign != 0)
				pentas[i].health = sign;
			if (boss_lifetime != 0 )
				pentas[i].boss_lifetime = boss_lifetime;
			else
				curr_boss++;
			return ;
		}
		i++;
	}
}

void	manage_penta(int *boss_spawn, int *health)
{
	int			frame_multi = *boss_spawn;

	frame_multi = get_frame_multi(frame_multi);
	*boss_spawn += 1;
	pentagram_frame.x = 360 * frame_multi;
	if (*boss_spawn >= 273)
	{
		*boss_spawn = (-1);
		*health = (-1);
	}
}

void	move_penta_from_player(SDL_Rect *dest)
{
	if (left_right == 1)
		dest->x -= speed;
	else if (left_right == 2)
		dest->x += speed;
	if (up_down == 1)
		dest->y += speed;
	else if (up_down == 2)
		dest->y -= speed;
}

void	pre_make_boss(t_enemy *enem, t_text_enemy text, SDL_Rect dest, int hp, int lifetime)
{
	enem->pos.x = dest.x;
	enem->pos.y = dest.y;
	enem->hbox.x = enem->pos.x;
	enem->hbox.y = enem->pos.y;
	make_boss(enem, text, hp, lifetime);
}

void	boss_make_prosess(t_enemy *enem, t_text_enemy text, SDL_Rect dest, int hp, int lifetime)
{
	int		i = 0, curr;
	double	min = 100000;
	t_vec	temp;
	double	len;

	while (i < E_COUNT)
	{
		if (enem[i].type == 0)
			return (pre_make_boss(&enem[i], text, dest, hp, lifetime));
		i++;
	}
	i = 0;
	while (i < E_COUNT)
	{
		if (enem[i].type != 4 && place_meeting(enem[i].hbox, screen) == 0)
			return (pre_make_boss(&enem[i], text, dest, hp, lifetime));
		i++;
	}
	i = 0;
	while (i < E_COUNT)
	{
		if (enem[i].type != 4)
		{
			temp.x = (enem[i].pos.x) - P_POS_X;
			temp.y = (enem[i].pos.y) - P_POS_Y;
			len = sqrt(temp.x * temp.x + temp.y * temp.y);
			if (min > len)
			{
				min = len;
				curr = i;
			}
			i++;
		}
	}
	pre_make_boss(&enem[curr], text, dest, hp, lifetime);
}

void	ascend_the_boss(t_enemy *enem, t_text_enemy text, t_graphics *all, t_bosses_penta *penta)
{
	int			sub;
	SDL_Rect	ascend, dest;

	ascend.w = 192;
	ascend.x = 0;
	ascend.y = 0;
	if (penta->boss_spawn > 100)
	{
		sub = penta->boss_spawn - 100;
		dest.x = penta->dest.x + 100;
		dest.y = penta->dest.y + 178 - sub;
		dest.w = text.boss.rect.w;
		dest.h = sub;
		ascend.h = sub;
		screen_shaker(&dest.x, &dest.y);
		if (place_meeting(ascend, screen))
			ysort(NULL, text.boss.text, &dest, &ascend, NULL, 0, 0 ,0);
//			make_curr_graph(all, text.boss.text, &dest, &ascend, NULL, 0, 0);
		if (penta->boss_spawn == 272)
			boss_make_prosess(enem, text, dest, penta->health, penta->boss_lifetime);
	}
}

void	check_flame_hit(t_vec point, SDL_Rect flame)
{
	double	len;
	t_vec	dist;

	dist.x = P_POS_X - point.x;
	dist.y = P_POS_Y - point.y;
	len = sqrt(dist.x * dist.x + dist.y * dist.y);
	if (len < 100)
	{
		if (place_meeting(phbox, flame))
			player_hit = 1;
	}
}

void	create_flame(t_text_enemy text, t_graphics *all, t_bosses_penta *penta)
{
	SDL_Rect	frame = {0, 0, 80, 80};
	t_vec		point;
	int			fr = 0;

	if (penta->boss_spawn >= 40)
	{
		if (penta->boss_spawn == 40)
			Mix_PlayChannel(12, flame_burst, 0);
		fr = 80 * ((penta->boss_spawn - 40) / 6);
		frame.x = fr;
		text.flame.rect.x = penta->dest.x + 60;
		text.flame.rect.y = penta->dest.y - 58;
		if (fr == 80)
		{
			point.x = penta->dest.x + 160;
			point.y = penta->dest.y + 115;
			check_flame_hit(point, text.flame.rect);
		}
		screen_shaker(&text.flame.rect.x, &text.flame.rect.y);
		ysort(NULL, text.flame.text, &text.flame.rect, &frame, NULL, 0, 0, 0);
	}
}

//the main function for creating the boss enemy
void	boss_spawner(t_enemy *enem, t_text_enemy *text, t_graphics *all, int sign, int boss_lifetime)
{
	static t_bosses_penta	pentas[20];
	int						i = 0;

	if (sign == START_INIT)
		return (init_struct(pentas));
	if (sign >= 0)
		return (penta_creator(pentas, text->clang, sign, boss_lifetime));
	while (i < 20)
	{
		if (pentas[i].boss_spawn != (-1))
		{
			if (sign == (-1))
			{
				manage_penta(&pentas[i].boss_spawn, &pentas[i].health);
				move_penta_from_player(&pentas[i].dest);
				screen_shaker(&pentas[i].dest.x, &pentas[i].dest.y);
				if (place_meeting(pentas[i].dest, screen))
					make_curr_graph(all, text->pentagram.text, &pentas[i].dest, &pentagram_frame, NULL, 0, 0);
			}
			else
				ascend_the_boss(enem, *text, all, &pentas[i]);
			create_flame(*text, all, &(pentas[i]));
		}
		i++;
	}
}
