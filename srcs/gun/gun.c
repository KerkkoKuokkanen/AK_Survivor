
#include "../top_down.h"

double	calc_a(t_vec v1, t_vec v2)
{
	double	a;
	double	b;
	double	c;

	a = v1.x * v2.x + v1.y * v2.y;
	b = sqrt(v1.x * v1.x + v1.y * v1.y);
	c = sqrt(v2.x * v2.x + v2.y * v2.y);
	return (acos(a / (b * c)));
}

int	degree(double angle)
{
	return ((angle * 180.f) / PI);
}

int	get_angle(int x, int y, SDL_Rect *gun)
{
	t_vec	v1;
	t_vec	v2;
	double	ang;
	int		deg;

	v1.x = 1;
	v1.y = 0;
	v2.x = gun->x - x;
	v2.y = gun->y - y;
	ang = calc_a(v1, v2);
	deg = degree(ang);
	if (gun->y > y && deg >= 90 && dir == 0)
		deg -= 180;
	else if (y > gun->y && deg <= 90 && dir == 1)
		deg *= (-1);
	else if (y >= gun->y && deg > 90)
		deg = (deg - 180) * (-1);
	return (deg);
}

void	recoil_pos_edge_cases(int y, double ty, SDL_Rect *pos)
{
	if (y > CENTER_Y)
	{
		if (angle == -90)
			pos->y += ty;
		else
			pos->y -= ty;
	}
	else
	{
		if (angle == -90)
			pos->y -= ty;
		else
			pos->y += ty;
	}
}

void	og_recoil(SDL_Rect *gun, int x, int y, double *tx, double *ty)
{
	*tx = 10 * cos(RAD * angle);
	*ty = 10 * sin(RAD * angle);
	if (x == CENTER_X)
		return (recoil_pos_edge_cases(y, *ty, gun));
	if (x < CENTER_X)
	{
		gun->x += *tx;
		gun->y += *ty;
		return ;
	}
	gun->x -= *tx;
	gun->y -= *ty;
}

void	make_recoil_for_gun(SDL_Rect *gun, int x, int y)
{
	static double	tx;
	static double	ty;
	static int		duration = 0;

	if (x < CENTER_X)
		gun->x = P_POS_X - 20;
	if (shot_happening == 1 || duration != 0)
	{
		if (shot_happening == 1)
		{
			og_recoil(gun, x, y, &tx, &ty);
			duration = 5;
			return ;
		}
		tx /= 2;
		ty /= 2;
		gun->x -= tx;
		gun->y -= ty;
		if (duration > 0)
			duration--;
	}
}

void	gun(t_tr gun, int x, int y, SDL_Rect player, t_graphics *all)
{
	SDL_Rect	gun_rotate;
	SDL_Point	rot;

	gun_rotate.x = CENTER_X;
	gun_rotate.y = CENTER_Y;
	angle = get_angle(x, y, &gun_rotate);
	make_recoil_for_gun(&gun.rect, x, y);
	rot.y = 32;
	rot.x = 20;
	screen_shaker(&gun.rect.x, &gun.rect.y);
	if (dir == 1)
	{
		rot.x = 34;
		ysort(NULL, gun.text, &gun.rect, NULL, &rot, angle, 1, 2);
//		make_curr_graph(all, gun.text, &gun.rect, NULL, &rot, angle, 1);
	}
	else
		ysort(NULL, gun.text, &gun.rect, NULL, &rot, angle, 0, 2);
//	make_curr_graph(all, gun.text, &gun.rect, NULL, &rot, angle, 0);
}
