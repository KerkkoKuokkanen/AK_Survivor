
#include "../top_down.h"
#define CIRCLE_DISTANCE 300.f
#define MIDDLE_POINT 665

t_vec	make_dir_for_arrow(t_vec *vec)
{
	t_vec	dir;

	dir.x = CENTER_X - (vec->x + 32);
	dir.y = CENTER_Y - (vec->y + 32);
	return (dir);
}

int	get_the_angle(t_vec dir, double *rad)
{
	t_vec	up = {0, 1};
	int		ang;

	*rad = calc_a(dir, up);
	ang = degree(*rad);
	return (ang);
}

void	get_the_sides(double rad, double *x_len, double *y_len, t_vec *dest, int *ang)
{
	if ((dest->x + 32) <= MIDDLE_POINT)
	{
		*ang = *ang * (-1);
		*y_len = CIRCLE_DISTANCE * -cos(rad) + CENTER_Y;
		*x_len = CIRCLE_DISTANCE * -sin(rad) + CENTER_X;
		return ;
	}
	*y_len = CIRCLE_DISTANCE * -cos(rad) + CENTER_Y;
	*x_len = CIRCLE_DISTANCE * sin(rad) + CENTER_X;
}

int	get_arrow_pulse(int frame_multi)
{
	double	f = frame_multi;
	double	ret = ((sin(f / 4 - 1.5) * 4) + 4);
	return (ret);
}

void	arrow_pulsing(SDL_Rect *dest)
{
	static int	pulse = 0;
	int			add;

	if (pulse > 25)
		pulse = 0;
	add = get_arrow_pulse(pulse);
	dest->x -= add;
	dest->w += (add + add);
	dest->y -= add;
	dest->h += (add + add);
	pulse++;
}

void	draw_arrow(int ang, t_vec *vec, t_graphics *all, double rad)
{
	double		x_len;
	double		y_len;
	get_the_sides(rad, &x_len, &y_len, vec, &ang);
	SDL_Rect	dest = {x_len - 16, y_len - 16, 32, 32};
	SDL_Point	rot = {16, 16};

	arrow_pulsing(&dest);
	make_curr_graph(all, arrow_pointer, &dest, NULL, &rot, ang, 0);
}

void	arrow_to_egg(t_graphics *all)
{
	if (!can_arrow)
		return ;
	t_vec	dir;
	t_vec	*vec = egg_main(NULL, NULL, 2);
	t_vec	temp;
	double	rad;
	int		ang;

	dir = make_dir_for_arrow(vec);
	ang = get_the_angle(dir, &rad);
	temp.x = vec->x + 32;
	temp.y = vec->y + 32;
	draw_arrow(ang, &temp, all, rad);
}
