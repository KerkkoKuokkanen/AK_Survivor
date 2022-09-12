
#include "../top_down.h"

void	make_the_extra_bullet_pos_one(t_bullets *bullet)
{
	const double	pos_diff = 20.f / 90.f;

	bullet->pos.y += pos_diff * (90 - abs(angle));
	if (angle < 0)
	{
		bullet->pos.x += pos_diff * abs(angle);
		return ;
	}
	bullet->pos.x -= pos_diff * (angle);
	bullet->hbox.x = bullet->pos.x;
	bullet->hbox.y = bullet->pos.y;
}

void	make_the_extra_bullet_pos_two(t_bullets *bullet)
{
	const double	pos_diff = 20.f / 90.f;

	bullet->pos.y -= pos_diff * (90 - abs(angle));
	if (angle < 0)
	{
		bullet->pos.x -= pos_diff * abs(angle);
		return ;
	}
	bullet->pos.x += pos_diff * (angle);
	bullet->hbox.x = bullet->pos.x;
	bullet->hbox.y = bullet->pos.y;
}

void	make_the_extra_bullet_pos_three(t_bullets *bullet)
{
	const double	pos_diff = 40.f / 90.f;

	bullet->pos.y += pos_diff * (90 - abs(angle));
	if (angle < 0)
	{
		bullet->pos.x += pos_diff * abs(angle);
		return ;
	}
	bullet->pos.x -= pos_diff * (angle);
	bullet->hbox.x = bullet->pos.x;
	bullet->hbox.y = bullet->pos.y;
}

void	make_the_extra_bullet_pos_four(t_bullets *bullet)
{
	const double	pos_diff = 40.f / 90.f;

	bullet->pos.y -= pos_diff * (90 - abs(angle));
	if (angle < 0)
	{
		bullet->pos.x -= pos_diff * abs(angle);
		return ;
	}
	bullet->pos.x += pos_diff * (angle);
	bullet->hbox.x = bullet->pos.x;
	bullet->hbox.y = bullet->pos.y;
}

void	create_the_extra_shot(t_bullets *bullets, int index, int additional_shots)
{
	int	i = 0;

	while (bullets[i].tru == 1)
		i++;
	bullets[i].tru = 1;
	bullets[i].life_time = 0;
	bullets[i].type = get_the_bullet_type();
	bullets[i].pos.x = bullets[index].pos.x;
	bullets[i].pos.y = bullets[index].pos.y;
	switch (additional_shots)
	{
		case 0:
			make_the_extra_bullet_pos_one(&bullets[i]);
			break ;
		case 1:
			make_the_extra_bullet_pos_two(&bullets[i]);
			break ;
		case 2:
			make_the_extra_bullet_pos_three(&bullets[i]);
			break ;
		case 3:
			make_the_extra_bullet_pos_four(&bullets[i]);
			break ;
	}
	bullets[i].dir = bullets[index].dir;
}

void	make_the_extra_popcorn_shots(t_bullets *bullets, int index)
{
	if (more_shots_at_a_time == 0)
		return ;
	int	additional_shots = 0;

	while (additional_shots < more_shots_at_a_time)
	{
		create_the_extra_shot(bullets, index, additional_shots);
		additional_shots++;
	}
}
