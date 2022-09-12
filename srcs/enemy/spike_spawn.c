
#include "../top_down.h"

// this function returns 1 if there are still enough free slots.
// 2 if there is enemy slots that could be used
// 0 if not possible
int		can_spike_spawn_happen(t_enemy *enemy, int amount)
{
	int	i = 0;
	int	empty_count = 0;	//enemy types that are 0 so not used
	int	usable_count = 0;	//enemies that are type 0 or off screen

	while (i < E_COUNT)
	{
		if (enemy[i].type == 0)
		{
			empty_count++;
			usable_count++;
		}
		else if (place_meeting(screen, enemy[i].text.rect) == 0)
			usable_count++;
		if (empty_count == amount)
			return (1);
		i++;
	}
	if (usable_count >= amount)
		return (2);
	return (0);
}

void	spike_iter_empty(t_enemy *enemy, int amount, t_text_enemy text)
{
	int	i = 0;
	int	count = 0;

	while (i < E_COUNT)
	{
		if (enemy[i].type == 0)
		{
			enemy[i].type = 0;
			choose_enemy(&enemy[i], text, 1);
			check_the_space_to_spawn(enemy, i);
			count++;
		}
		if (count == amount)
			break ;
		i++;
	}
}

void	spike_iter_usable(t_enemy *enemy, int amount, t_text_enemy text)
{
	int	i = 0;
	int	count = 0;

	while (i < E_COUNT)
	{
		if (enemy[i].type != 4 &&
			(enemy[i].type == 0 || place_meeting(screen, enemy[i].text.rect) == 0))
		{
			enemy[i].type = 0;
			choose_enemy(&enemy[i], text, 1);
			check_the_space_to_spawn(enemy, i);
			count++;
		}
		if (count == amount)
			break ;
		i++;
	}
}

void	spike_spawn(t_enemy *enemy, int amount, t_text_enemy text)
{
	int	can_spike = can_spike_spawn_happen(enemy, amount);

	if (can_spike == 0)
		return ;
	spike_spawn_active = 0;
	if (can_spike == 1)
	{
		spike_iter_empty(enemy, amount, text);
		return ;
	}
	spike_iter_usable(enemy, amount, text);
}

int	spike_amount_table()
{
	static const int	table[4] = {100, 350, 220, 180};
	int					ret = 230;
	static int			one_two = 0;

	if (current_spikespawn_index < 4)
		ret = table[current_spikespawn_index];
	current_spikespawn_index++;
	if (all_seconds > 530)
		return (350);
	if (all_seconds > 290)
	{
		if (one_two == 0)
		{
			one_two = 1;
			return (ret);
		}
		one_two = 0;
		return (260);
	}
	return (ret);
}
