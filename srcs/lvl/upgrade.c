
#include "../top_down.h"

void	upgrade_chosen_attribute(uint8_t bool, int *exhaust, int *amount)
{
	switch (bool)
	{
		case 1:
			health_main(NULL, NULL, NULL, 4);
			amount[0]++;
			break ;
		case 2:
			if (reload_speed > 15)
			{
				amount[1]++;
				reload_speed -= 5;
			}
			if (reload_speed == 15)
			{
				amount[1] = (-1);
				exhaust[0] = 1;
			}
			break ;
		case 3:
			if (fire_rate > 2)
			{
				amount[2]++;
				fire_rate -= 1;
			}
			if (fire_rate == 2)
			{
				amount[2] = (-1);
				exhaust[1] = 1;
			}
			break ;
		case 4:
			if (split_shot_amount < 4)
			{
				amount[3]++;
				split_shot_amount += 1;
			}
			if (split_shot_amount == 4)
			{
				amount[3] = (-1);
				exhaust[2] = 1;
			}
			break ;
		case 5:
			if (more_shots_at_a_time < 4)
			{
				amount[4]++;
				more_shots_at_a_time += 1;
			}
			if (more_shots_at_a_time == 4)
			{
				amount[4] = (-1);
				exhaust[3] = 1;
			}
			break ;
		case 6:
			if (insta_kill_active < 15)
			{
				amount[5]++;
				insta_kill_active += 3;
			}
			if (insta_kill_active == 15)
			{
				amount[5] = (-1);
				exhaust[4] = 1;
			}
			break ;
		case 7:
			real_speed += 1;
			amount[6]++;
			break ;
		case 8:
			if (max_shots < 30)
			{
				amount[7]++;
				max_shots += 5;
			}
			if (max_shots == 30)
			{
				amount[7] = (-1);
				exhaust[6] = 1;
			}
			break ;
		case 9:
			if (shock_active < 4)
			{
				amount[8]++;
				shock_active += 1;
			}
			if (shock_active == 4)
			{
				amount[8] = (-1);
				exhaust[7] = 1;
			}
			break ;
		case 10:
			rage_active = 1;
			rage_sprite = 1;
			amount[9]++;
			break ;
		case 11:
			if (creep_active < 5)
			{
				amount[10]++;
				creep_active += 1;
			}
			if (creep_active == 5)
			{
				amount[10] = (-1);
				exhaust[9] = 1;
			}
			break ;
		case 12:
			if (dead_whale_active < 5)
			{
				amount[11]++;
				dead_whale_active += 1;
			}
			if (dead_whale_active == 5)
			{
				amount[11] = (-1);
				exhaust[10] = 1;
			}
			break ;
		case 13:
			if (dagger_active < 4)
			{
				amount[12]++;
				dagger_active += 1;
			}
			if (dagger_active == 4)
			{
				amount[12] = (-1);
				exhaust[11] = 1;
			}
			break ;
		case 14:
			dark_aura_active = 1;
			amount[13]++;
			break ;
	}
}
