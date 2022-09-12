
#include "../top_down.h"

typedef struct	s_indexx
{
	int		index;
	double	y;
	uint8_t	player;
}				t_indexx;

typedef struct	s_sprite
{
	t_tex		text;
	SDL_Rect	dest;
	SDL_Rect	frame;
	SDL_Point	point;
	int			angle;
	int			sign;
	uint8_t		player;
	int			nulls;
}				t_sprite;

int	indexx_cmp_func(const void *a, const void *b)
{
	t_indexx *aa = (t_indexx *)a;
	t_indexx *bb = (t_indexx *)b;
	return (aa->y - bb->y);
}

void	sort_the_ysort(t_graphics *all, t_sprite *sprites, int amount, t_sprite *gun_save)
{
	t_indexx	index[SPRITE_AMOUNT];
	int		i = 0;

	while (i < amount)
	{
		index[i].index = i;
		index[i].y = sprites[i].dest.y + sprites[i].dest.h;
		index[i].player = sprites[i].player;
		i++;
	}
	qsort(index, amount, sizeof(t_indexx), indexx_cmp_func);
	i = 0;
	while (i < amount && i < SPRITE_AMOUNT)
	{
		switch (sprites[index[i].index].nulls)
		{
			case 0:
				make_curr_graph(all, sprites[index[i].index].text,
							NULL, NULL, NULL,
							sprites[index[i].index].angle,
							sprites[index[i].index].sign);
				break ;
			case 1:
				make_curr_graph(all, sprites[index[i].index].text,
							&sprites[index[i].index].dest, NULL, NULL,
							sprites[index[i].index].angle,
							sprites[index[i].index].sign);
				break ;
			case 2:
				make_curr_graph(all, sprites[index[i].index].text,
							NULL, &sprites[index[i].index].frame, NULL,
							sprites[index[i].index].angle,
							sprites[index[i].index].sign);
				break ;
			case 3:
				make_curr_graph(all, sprites[index[i].index].text,
							NULL, NULL, &sprites[index[i].index].point,
							sprites[index[i].index].angle,
							sprites[index[i].index].sign);
				break ;
			case 4:
				make_curr_graph(all, sprites[index[i].index].text,
							&sprites[index[i].index].dest, &sprites[index[i].index].frame, NULL,
							sprites[index[i].index].angle,
							sprites[index[i].index].sign);
				break ;
			case 5:
				make_curr_graph(all, sprites[index[i].index].text,
							&sprites[index[i].index].dest, NULL,
							&sprites[index[i].index].point, sprites[index[i].index].angle,
							sprites[index[i].index].sign);
				break ;
			case 6:
				make_curr_graph(all, sprites[index[i].index].text,
							NULL, &sprites[index[i].index].frame,
							&sprites[index[i].index].point, sprites[index[i].index].angle,
							sprites[index[i].index].sign);
				break ;
			case 7:
				make_curr_graph(all, sprites[index[i].index].text,
							&sprites[index[i].index].dest, &sprites[index[i].index].frame,
							&sprites[index[i].index].point, sprites[index[i].index].angle,
							sprites[index[i].index].sign);
				break ;
		}
		if (sprites[index[i].index].player == 1)
			make_curr_graph(all, gun_save->text, &gun_save->dest, NULL, &gun_save->point, gun_save->angle, gun_save->sign);
		i++;
	}
}

void	ysort(t_graphics *all, t_tex text, SDL_Rect *dest, SDL_Rect *frame, SDL_Point *point, int kulma, int sign, int call_from)
{
	static t_sprite	sprites[SPRITE_AMOUNT] = { 0 };
	static t_sprite	gun_save;
	static int		amount = 0;
	int				count = 0;

	if (call_from == 2)
	{
		gun_save.text = text;
		gun_save.dest = *dest;
		gun_save.point = *point;
		gun_save.angle = kulma;
		gun_save.sign = sign;
		gun_save.player = 0;
		return ;
	}
	if (call_from == (-1))
	{
		sort_the_ysort(all, sprites, amount, &gun_save);
		bzero(sprites, sizeof(t_sprite) * SPRITE_AMOUNT);
		amount = 0;
		return ;
	}
	sprites[amount].text = text;
	if (dest != NULL)
	{
		sprites[amount].dest = *dest;
		count += 1;
	}
	if (frame != NULL)
	{
		sprites[amount].frame = *frame;
		count += 2;
	}
	if (point != NULL)
	{
		sprites[amount].point = *point;
		count += 4;
	}
	make_nulls(&sprites[amount].nulls, count);
	sprites[amount].angle = 0;
	sprites[amount].sign = sign;
	sprites[amount].player = 0;
	if (call_from == 1)
		sprites[amount].player = 1;
	amount++;
}
