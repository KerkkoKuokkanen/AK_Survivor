
#include "../top_down.h"

void	spike_time_spawn()
{
	if (all_seconds % SPIKE_DELAY == 0 && time_to_spike != all_seconds)
	{
		spike_spawn_active = 1;
		time_to_spike = all_seconds;
	}
}

void	make_coord_for_enemy(t_enemy *enem)
{
	float	rad = float_rand();
	int		rand_dist = (rand() % 400) + 1200;

	enem->pos.x = (cos(rad) * rand_dist) + CENTER_X;
	enem->pos.y = (sin(rad) * rand_dist) + CENTER_Y;
	enem->text.rect.x = enem->pos.x;
	enem->text.rect.y = enem->pos.y;
	enem->hbox.x = enem->pos.x;
	enem->hbox.y = enem->pos.y;
}

int	check_the_space_to_spawn(t_enemy *enem, int i)
{
	int			x, y = 0;
	uint8_t		bool;

	while (y < 20)
	{
		make_coord_for_enemy(&enem[i]);
		x = 0;
		bool = 0;
		while (x < E_COUNT)
		{
			if (enem[x].type != 0 && x != i)
			{
				if (enem[i].hbox.x == enem[x].hbox.x && enem[i].hbox.y == enem[x].hbox.y)
				{
					break ;
					bool = 1;
				}
			}
			x++;
		}
		if (bool == 0)
			return (1);
		y++;
	}
	enem[i].type = 0;
	return (0);
}

int	get_the_spawn_time()
{
	if (all_seconds % 6 == 0)
	{
		if (check_of_the_spawn == all_seconds)
			return (0);
		check_of_the_spawn = all_seconds;
		return (1);
	}
	return (0);
}

int	boss_time()
{
	static int	bosses[20] = {190, 250, 340, 349, 420, 450, 452, 510, 513, 515, 518, 534, 536, 538, 540, 542, 544, 546, 548, 550};
	int			i = 0;

	while (i < 20)
	{
		if (all_seconds >= bosses[i])
		{
			if (current_boss_index < (i + 1))
			{
				current_boss_index += 1;
				return (1);
			}
		}
		else
			return (0);
		i++;
	}
	return (0);
}

int	enemy_spawner_time(t_enemy *enem, t_text_enemy text)
{
	enemy_timer++;
	if (boss_time())
	{
		spawn_boss = 1;
		return (1);
	}
	if (enemy_timer >= spawn_enemy_delayer)
	{
		enemy_timer = 0;
		if (spawn_enemy_delayer > 5)
			spawn_enemy_delayer -= get_the_spawn_time();
		return (1);
	}
	return (0);
}

void	move_enemy_from_player(t_vec *dest)
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

void	choose_move_or_push(t_enemy *enem, int i, t_text_enemy text)
{
	if (enem[i].push_back_amount != 0 && (enem[i].got_shot || enem[i].push.duration != 0))
		push_back_main(enem, i);
	else
		move_main(enem, i, text);
}

void	iter_with_spawn(t_enemy *enem, t_text_enemy text, t_graphics *all)
{
	static int	spawn_amount = 4;
	int			i = 0, count = 0;

	while (i < E_COUNT)
	{
		if (spawn_boss == 1)
		{
			boss_spawner(&enem[i], &text, all, 0, 0);
			count = spawn_amount;
			spawn_boss = 0;
		}
		if (enem[i].type == 0 && count < spawn_amount && spike_spawn_active == 0)
		{
			choose_enemy(&enem[i], text, 0);
			check_the_space_to_spawn(enem, i);
			count++;
		}
		if (enem[i].type != 0)
		{
			move_enemy_from_player(&enem[i].pos);
			update_enem_hbox(&enem[i]);
			choose_move_or_push(enem, i, text);
		}
		i++;
	}
	sort_enemy_array(enem, all);
	boss_spawner(enem, &text, all, (-2), 0);
}

void	iter_no_spawn(t_enemy *enem, t_text_enemy text,  t_graphics *all)
{
	int	i = 0;
	int	count = 0, bool = 1;

	while (i < E_COUNT)
	{
		if (i > 550)
			bool = 0;
		if (enem[i].type != 0)
		{
			move_enemy_from_player(&enem[i].pos);
			update_enem_hbox(&enem[i]);
			choose_move_or_push(enem, i, text);
		}
		else if (bool == 1 && (all_seconds % 5) == 0 && weak_spawn_checker != all_seconds)
		{
			if (count < 30)
			{
				bool = weak_enem_spawn(enem, text, i);
				count++;
			}
		}
		i++;
	}
	weak_spawn_checker = all_seconds;
	sort_enemy_array(enem, all);
	boss_spawner(enem, &text, all, (-2), 0);
}

void	enemy_main(t_enemy *enem, t_text_enemy text, t_graphics *all)
{
	int	amount;

	spike_time_spawn();
	if (spike_spawn_active == 1)
	{
		amount = spike_amount_table();
		spike_spawn(enem, amount, text);
	}
	if (enemy_spawner_time(enem, text))
		iter_with_spawn(enem, text, all);
	else
		iter_no_spawn(enem, text, all);
}
