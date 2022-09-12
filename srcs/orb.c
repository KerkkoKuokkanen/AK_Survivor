
#include "top_down.h"

void	init_orb(t_orb *orbs)
{
	int	i = 0;

	bzero(orbs, sizeof(t_orb) * (ORB_AMOUNT + 1));
	while (i < ORB_AMOUNT)
	{
		orbs[i].amount = 0;
		orbs[i].pos.w = 16;
		orbs[i].pos.h = 16;
		orbs[i].hit = 0;
		i++;
	}
}

void	move_orb(int *x, int *y)
{
	if (left_right == 1)
		*x -= speed;
	else if (left_right == 2)
		*x += speed;
	if (up_down == 1)
		*y += speed;
	else if (up_down == 2)
		*y -= speed;
}

t_vec	calculate_vec_for_orb(t_orb *orb, double *len)
{
	t_vec	vec;

	vec.x =  orb->pos.x - CENTER_X;
	vec.y =  orb->pos.y - CENTER_Y;
	*len = sqrt(vec.x * vec.x + vec.y * vec.y);
	vec.x /= *len;
	vec.y /= *len;
	return (vec);
}

void	orb_hit(t_orb *orb, Mix_Chunk **coin)
{
	double	len = 1000;
	int		amount = 0;

	if (orb->hit == 0)
	{
		if (place_meeting(big_phbox, orb->pos))
			orb->hit = 1;
	}
	if (orb->hit == 1)
	{
		orb->dir = calculate_vec_for_orb(orb, &len);
		if (len < 15)
		{
			Mix_PlayChannel(6, coin[1], 0);
			orb->hit = 0;
			amount = orb->amount;
			orb->amount = 0;
		}
		orb->pos.x -= orb->dir.x * 7;
		orb->pos.y -= orb->dir.y * 7;
	}
	level_up_main(NULL, amount, NULL, NULL, NULL, NULL, NULL, 0);
}

void	iter_and_draw_orbs(t_orb *orbs, t_graphics *all, t_tex orb, Mix_Chunk **coin)
{
	int	i = 0;

	while (i < ORB_AMOUNT)
	{
		if (orbs[i].amount != 0)
		{
			move_orb(&orbs[i].pos.x, &orbs[i].pos.y);
			screen_shaker(&orbs[i].pos.x, &orbs[i].pos.y);
			orb_hit(&orbs[i], coin);
			if (place_meeting(screen, orbs[i].pos))
			{
				orbs[i].on_screen = 1;
				orb_rect.x = 16 * orbs[i].sprite_index;
				make_curr_graph(all, orb, &orbs[i].pos, &orb_rect, NULL, 0, 0);
			}
			else
				orbs[i].on_screen = 0;
		}
		i++;
	}
}

void	make_orb_amount_and_sprite_index(t_enemy *enem, t_orb *orb)
{
	switch (enem->type)
	{
		case (1):
			orb->amount += 1;
			orb->sprite_index = 0;
			break ;
		case (2):
			orb->amount += 2;
			orb->sprite_index = 1;
			break ;
		case (3):
			orb->amount += all_seconds / 8 + 1;
			orb->sprite_index = 3;
			break ;
		case (4):
			orb->amount += 1000;
			orb->sprite_index = 2;
			break ;
		case (5):
			orb->amount += 4;
			orb->sprite_index = 4;
			break ;
		case (6):
			orb->amount += 8;
			orb->sprite_index = 5;
			break ;
		case (7):
			orb->amount += 30;
			orb->sprite_index = 6;
			break ;
		case (8):
			orb->amount += 48;
			orb->sprite_index = 7;
			break ;
		case (9):
			orb->amount += 74;
			orb->sprite_index = 8;
			return ;
	}
	if (orb->amount > 1000)
		orb->amount = 1000;
}

void	create_orb(t_enemy *enem, t_orb *orb)
{
	orb->pos.x = enem->hbox.x + enem->hbox.w / 2;
	orb->pos.y = enem->hbox.y + enem->hbox.h / 2;
	orb->hit = 0;
	make_orb_amount_and_sprite_index(enem, orb);
}

void	the_orb_god_mother(t_enemy *enem, t_orb *orbs, int curr_e)
{
	int	i = 0;

	while (i < ORB_AMOUNT)
	{
		if (orbs[i].amount == 0)
		{
			create_orb(&enem[curr_e], &orbs[i]);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < ORB_AMOUNT)
	{
		if (orbs[i].on_screen == 0)
		{
			create_orb(&enem[curr_e], &orbs[i]);
			return ;
		}
		i++;
	}
}

void	orb_main(t_enemy *enem, t_graphics *all, t_tex *orb, Mix_Chunk **coin, int sign)
{
	static t_orb	orbs[ORB_AMOUNT + 1];

	if (sign == START_INIT)
		return (init_orb(orbs));
	else if (sign != (-2))
	{
		the_orb_god_mother(enem, orbs, sign);
		return ;
	}
	iter_and_draw_orbs(orbs, all, *orb, coin);
}
