
#include "../top_down.h"

float	new_float_rand()
{
	float	scale = ((double)rand() / (double)(RAND_MAX));
	return (scale * (PI / 2));
}

void	vec_random_rotate(t_vec *vec)
{
	float	angle = new_float_rand();
	int		sign = rand();
	int		multi = 1;

	if (sign % 2 == 0)
		multi = (-1);
	angle *= multi;
	vec->x = vec->x * cos(angle) - vec->y * sin(angle);
	vec->y = vec->x * sin(angle) + vec->y * cos(angle);
}

void	normalize_vec(t_vec *vec)
{
	double	len;

	len = sqrt(vec->x * vec->x + vec->y * vec->y);
	vec->x /= len;
	vec->y /= len;
}

void	create_new_shot(t_bullets *bullets, int index)
{
	int	i = 0;

	while (bullets[i].tru == 1)
		i++;
	bullets[i].tru = 1;
	bullets[i].life_time = 0;
	bullets[i].type = 2;
	bullets[i].dir.x = bullets[index].dir.x * (-1);
	bullets[i].dir.y = bullets[index].dir.y * (-1);
	vec_random_rotate(&bullets[i].dir);
	normalize_vec(&bullets[i].dir);
	bullets[i].pos.x = bullets[index].pos.x + (bullets[i].dir.x);
	bullets[i].pos.y = bullets[index].pos.y + (bullets[i].dir.y);
	bullets[i].hbox.x = bullets[i].pos.x;
	bullets[i].hbox.y = bullets[i].pos.y;
}

void	fractal_shot_creator(t_bullets *bullets, int index)
{
	if (split_shot_amount == 0 || bullets[index].type == 2)
		return ;

	int	additional_shot_count = 0;

	while (additional_shot_count < split_shot_amount)
	{
		create_new_shot(bullets, index);
		additional_shot_count++;
	}
}
