
#include "../top_down.h"
#define UPGRAGE_NUM 13

void	make_first_second(int *first, int *second, int choose)
{
	if (*first == (-1))
	{
		*first = choose;
		return ;
	}
	if (*second == (-1))
		*second = choose;
}

int		get_pool(int *exhaust)
{
	int	i = 0;
	int	count = 0;

	while (i < UPGRAGE_NUM)
	{
		if (exhaust[i] == 1)
			count++;
		i++;
	}
	return (UPGRAGE_NUM - count);
}

void	get_the_right_lvlup(t_itr *this, t_level_up *lvl, int choose)
{
	this->index = choose;
	this->tr = lvl->lvlup_tex[choose];
}

int		get_the_right_from_choose(int choose, int *exhaust)
{
	int	i = 0;
	int	count = 0;

	if (choose == 0)
		return (0);
	while (i < UPGRAGE_NUM)
	{
		if (exhaust[i] == 0)
			count++;
		if (count == choose)
			return (i + 1);
		i++;
	}
	return (0);
}

void	choose_one_two_three(t_itr *one, t_itr *two, t_itr *three, t_level_up *lvl, int *exhaust)
{
	int	first = (-1), second = (-1);
	int	health_index = health_main(NULL, NULL, NULL, 3);
	int	choose, right;
	int	pool = get_pool(exhaust);
	int	count = 0;

	while (count < 3)
	{
		choose = (rand() % pool) + 1;
		if (count == 2 && health_index != 2)
			choose = 0;
		if (choose != first && choose != second)
		{
			make_first_second(&first, &second, choose);
			right = get_the_right_from_choose(choose, exhaust);
			switch (count)
			{
				case 0:
					get_the_right_lvlup(one, lvl, right);
					break ;
				case 1:
					get_the_right_lvlup(two, lvl, right);
					break ;
				case 2:
					get_the_right_lvlup(three, lvl, right);
					break ;
			}
			count++;
		}
	}
}
