
#include "../top_down.h"

void	put_mag_to_screen(int shot_count, t_tex mag, t_graphics *all)
{
	int	x, y = 0;
	int	i = 0;
	int	odd_even = 0;
	int	shots_left = max_shots - shot_count;
	
	mag_pos.y = 10;
	mag_pos.x = 1175;
	while (y < max_shots)
	{
		x = 0;
		while (x < 5)
		{
			if (shots_left <= i)
				mag_full_empty.x = 16;
			else
				mag_full_empty.x = 0;
			make_curr_graph(all, mag, &mag_pos, &mag_full_empty, NULL, 0, 0);
			mag_pos.x += 10;
			x++;
			i++;
		}
		if (odd_even == 0)
			odd_even = 1;
		else
		{
			mag_pos.x = 1175;
			mag_pos.y += 18;
			odd_even = 0;
		}
		y += 5;
	}
}

void	mag_main(int shot_count, t_tex mag, t_graphics *all)
{
	put_mag_to_screen(shot_count, mag, all);
}
