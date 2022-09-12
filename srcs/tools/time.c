
#include "../top_down.h"

void	rage_time_active(int *time)
{
	if (rage_active == 1)
	{
		rage_flame(NULL, NULL, (-1));
		Mix_PlayChannel(11, rage_scream, 0);
		Mix_PlayChannel(19, flame_burst, 0);
		rage_active = 0;
		rage_now = 1;
		*time = 600;
		return ;
	}
	if (rage_now > 0)
	{
		*time -= 1;
		if (*time <= 0)
			rage_now = 0;
	}
}

void	manage_seconds_and_minutes(int time, int *seconds, int *minutes)
{
	*seconds += time;
	if (*seconds == 60)
	{
		*seconds = 0;
		*minutes += 1;
	}
}

int	get_the_num_from_time(int time, int sign)
{
	if (sign == 0)
	{
		if (time >= 10)
			return ((time / 10) % 10);
		return (0);
	}
	return (time % 10);
}

void	put_time_to_screen(int seconds, int minutes, t_graphics *all, t_tex nums, t_tex dots)
{
	int			i = 0;

	time_pos.x = 594;
	while (i < 4)
	{
		switch (i)
		{
			case 0:
				time_frame_pos.x = NUM_JUMP * get_the_num_from_time(minutes, 0);
				break ;
			case 1:
				time_frame_pos.x = NUM_JUMP * get_the_num_from_time(minutes, 1);
				break ;
			case 2:
				time_frame_pos.x = NUM_JUMP * get_the_num_from_time(seconds, 0);
				break ;
			case 3:
				time_frame_pos.x = NUM_JUMP * get_the_num_from_time(seconds, 1);
				break ;
		}
		make_curr_graph(all, nums, &time_pos, &time_frame_pos, NULL, 0, 0);
		if (i == 1)
			time_pos.x += 30;
		else
			time_pos.x += 20;
		i++;
	}
	make_curr_graph(all, dots, &dots_pos, NULL, NULL, 0, 0);
}

void	time_main(int time, t_graphics *all, t_tex *nums, t_tex *dots, int sign)
{
	static int	seconds = 0;
	static int	minutes = 0;
	static int	rage_time = 0;

	if (sign == START_INIT)
	{
		seconds = 0;
		minutes = 0;
		time = 0;
		return ;
	}
	if (sign == 0)
		return (manage_seconds_and_minutes(time, &seconds, &minutes));
	put_time_to_screen(seconds, minutes, all, *nums, *dots);
	rage_time_active(&rage_time);
	lazy_minute_get_variable = minutes;
	lazy_second_get_variable = seconds;
}
