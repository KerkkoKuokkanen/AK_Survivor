
#include "../top_down.h"

//because the player itself does not move we use this function to scroll many
//of the textures in the game to create a moving effect
//left_right and up_down are globals that tell us the direction
void	move_dest_from_player(t_vec *dest)
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

void	manage_screen_shake()
{
	static int	active = 0;

	if (s_shake_active != 0 && active == 0)
	{
		if (s_shake_active == 2)
			screen_shake_amount = 10;
		active = 4;
		s_shake_active = 0;
	}
	switch (active)
	{
		case 4:
			sh_x = -screen_shake_amount;
			sh_y = -screen_shake_amount;
			active--;
			break ;
		case 3:
			sh_x = screen_shake_amount;
			sh_y = -screen_shake_amount;
			active--;
			break ;
		case 2:
			sh_x = -screen_shake_amount;
			sh_y = screen_shake_amount;
			active--;
			break ;
		case 1:
			sh_x = screen_shake_amount;
			sh_y = screen_shake_amount;
			active--;
			break ;
		case 0:
			sh_x = 0;
			sh_y = 0;
			break ;
	}
}

void	screen_shaker(int *x, int *y)
{
	*x += sh_x;
	*y += sh_y;
}

int	figure_the_delay(clock_t start, clock_t end)
{
	double	time;
	int		ret;

	time = 0.0;
	time += (double)(end - start) / CLOCKS_PER_SEC;
	ret = FRAME - (int)(time * 1000);
	if (ret < 0)
		return (0);
	else
		return (ret);
}

t_tex	get_texture(SDL_Renderer *rend, char *filepath)
{
	SDL_Surface	*surface = IMG_Load(filepath);
	t_tex		tr;

	tr.text = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	return (tr);
}

int	y_place_meeting(SDL_Rect box, SDL_Rect hit)
{
	if (hit.y < (box.y + box.h) && (hit.y + hit.h) > box.y)
		return (1);
	return (0);
}

int	x_place_meeting(SDL_Rect box, SDL_Rect hit)
{
	if (hit.x < (box.x + box.w) && (hit.x + hit.w) > box.x)
		return (1);
	return (0);
}

int	place_meeting(SDL_Rect box, SDL_Rect hit)
{
	if (x_place_meeting(box, hit) && y_place_meeting(box, hit))
		return (1);
	return (0);
}

int	point_meeting(int x, int y, SDL_Rect box)
{
	if (x > box.x && x < (box.x + box.w)
		&& y > box.y && y < (box.y + box.h))
		return (1);
	return (0);
}

float	float_rand()
{
	float	scale = ((double)rand() / (double)(RAND_MAX));
	return (scale * (PI * 2));
}

void	bigger_smaller_rect(SDL_Rect *one, SDL_Rect *two, SDL_Rect *three, int x, int y, int sign)
{
	static int	a = 0;
	static int	b = 0;
	static int	c = 0;

	if (sign == 1)
	{
		a = 0;
		b = 0;
		c = 0;
		return ;
	}
	if (point_meeting(x, y, *one))
	{
		if (a < 5)
		{
			one->x -= 2;
			one->w += 4;
			one->y -= 4;
			one->h += 8;
			a++;
		}
	}
	else if (a > 0)
	{
		one->x += 2;
		one->w -= 4;
		one->y += 4;
		one->h -= 8;
		a--;
	}
	if (point_meeting(x, y, *two))
	{
		if (b < 5)
		{
			two->x -= 2;
			two->w += 4;
			two->y -= 4;
			two->h += 8;
			b++;
		}
	}
	else if (b > 0)
	{
		two->x += 2;
		two->w -= 4;
		two->y += 4;
		two->h -= 8;
		b--;
	}
	if (point_meeting(x, y, *three))
	{
		if (c < 5)
		{
			three->x -= 2;
			three->w += 4;
			three->y -= 4;
			three->h += 8;
			c++;
		}
	}
	else if (c > 0)
	{
		three->x += 2;
		three->w -= 4;
		three->y += 4;
		three->h -= 8;
		c--;
	}
}

void	make_nulls(int *nulls, int i)
{
	switch (i)
	{
		case 0:
			*nulls = 0;
			break ;
		case 1:
			*nulls = 1;
			break ;
		case 2:
			*nulls = 2;
			break ;
		case 4:
			*nulls = 3;
			break ;
		case 3:
			*nulls = 4;
			break ;
		case 5:
			*nulls = 5;
			break ;
		case 6:
			*nulls = 6;
			break ;
		case 7:
			*nulls = 7;
			break ;
	}
}

void	put_images_to_screen(SDL_Renderer *rend, t_graphics *all)
{
	int			i = 0;
	SDL_Rect	dest;

	while (i < curr_sprite && i < SPRITE_AMOUNT)
	{
		switch (all[i].nulls)
		{
			case 0:
				SDL_RenderCopyEx(rend, all[i].tex.text,
							NULL, NULL,
							all[i].angle, NULL,
							all[i].sign);
				break ;
			case 1:
				dest = scale_the_rect(all[i].dest);
				SDL_RenderCopyEx(rend, all[i].tex.text,
							NULL, &dest,
							all[i].angle, NULL,
							all[i].sign);
				break ;
			case 2:
				SDL_RenderCopyEx(rend, all[i].tex.text,
							&all[i].frame, NULL,
							all[i].angle, NULL,
							all[i].sign);
				break ;
			case 3:
				SDL_RenderCopyEx(rend, all[i].tex.text,
							NULL, NULL,
							all[i].angle, &all[i].point,
							all[i].sign);
				break ;
			case 4:
				dest = scale_the_rect(all[i].dest);
				SDL_RenderCopyEx(rend, all[i].tex.text,
							&all[i].frame, &dest,
							all[i].angle, NULL,
							all[i].sign);
				break ;
			case 5:
				dest = scale_the_rect(all[i].dest);
				SDL_RenderCopyEx(rend, all[i].tex.text,
							NULL, &dest,
							all[i].angle, &all[i].point,
							all[i].sign);
				break ;
			case 6:
				SDL_RenderCopyEx(rend, all[i].tex.text,
							&all[i].frame, NULL,
							all[i].angle, &all[i].point,
							all[i].sign);
				break ;
			case 7:
				dest = scale_the_rect(all[i].dest);
				SDL_RenderCopyEx(rend, all[i].tex.text,
							&all[i].frame, &dest,
							all[i].angle, &all[i].point,
							all[i].sign);
				break ;
		}
		i++;
	}
}

void	make_curr_graph(t_graphics *all, t_tex text, SDL_Rect *dest, SDL_Rect *frame, SDL_Point *point, int angle, int sign)
{
	int	i = 0;

	all[curr_sprite].tex = text;
	if (dest != NULL)
	{
		all[curr_sprite].dest = *dest;
		i += 1;
	}
	if (frame != NULL)
	{
		all[curr_sprite].frame = *frame;
		i += 2;
	}
	if (point != NULL)
	{
		all[curr_sprite].point = *point;
		i += 4;
	}
	make_nulls(&all[curr_sprite].nulls, i);
	all[curr_sprite].angle = angle;
	all[curr_sprite].sign = sign;
	curr_sprite++;
}

void	enem_kill_counter(t_enemy *enem)
{
	if (enem->type == 4)
		bosses_killed_during_game += 1;
	enemies_killed_during_game += 1;
}

void	clear_screen(t_graphics *all, size_t size)
{
	curr_sprite = 0;
	bzero(all, sizeof(t_graphics) * E_COUNT);
}

void	bigger_smaller_indicator(SDL_Rect *one, SDL_Rect *two, int x, int y, int sign)
{
	static int	a = 0;
	static int	b = 0;

	if (sign == 1)
	{
		a = 0;
		b = 0;
		return ;
	}
	if (point_meeting(x, y, scale_the_rect(*one)))
	{
		if (a < 5)
		{
			one->x -= 1;
			one->w += 2;
			one->y -= 2;
			one->h += 4;
			a++;
		}
	}
	else if (a > 0)
	{
		one->x += 1;
		one->w -= 2;
		one->y += 2;
		one->h -= 4;
		a--;
	}
	if (point_meeting(x, y, scale_the_rect(*two)))
	{
		if (b < 5)
		{
			two->x -= 1;
			two->w += 2;
			two->y -= 2;
			two->h += 4;
			b++;
		}
	}
	else if (b > 0)
	{
		two->x += 1;
		two->w -= 2;
		two->y += 2;
		two->h -= 4;
		b--;
	}
}
