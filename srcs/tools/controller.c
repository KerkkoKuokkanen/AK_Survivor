
#include "../top_down.h"
#define SHOULDER_DEAD 6000

void	stick_to_keys(t_keys *keys)
{
	switch (stick.stick_angle)
	{
		case 1:
			keys->left = 0;
			keys->right = 0;
			keys->up = 0;
			keys->down = 0;
			break ;
		case 0:
			keys->left = 0;
			keys->right = 1;
			keys->up = 0;
			keys->down = 0;
			break ;
		case 45:
			keys->left = 0;
			keys->right = 1;
			keys->up = 0;
			keys->down = 1;
			break ;
		case 90:
			keys->left = 0;
			keys->right = 0;
			keys->up = 0;
			keys->down = 1;
			break ;
		case 135:
			keys->left = 1;
			keys->right = 0;
			keys->up = 0;
			keys->down = 1;
			break ;
		case 180:
			keys->left = 1;
			keys->right = 0;
			keys->up = 0;
			keys->down = 0;
			break ;
		case (-45):
			keys->left = 0;
			keys->right = 1;
			keys->up = 1;
			keys->down = 0;
			break ;
		case (-90):
			keys->left = 0;
			keys->right = 0;
			keys->up = 1;
			keys->down = 0;
			break ;
		case (-135):
			keys->left = 1;
			keys->right = 0;
			keys->up = 1;
			keys->down = 0;
			break ;
	}
}

void	calculate_stick_angles(int x, int y)
{
	t_vec			dir = {P_POS_X - x, P_POS_Y - y};
	double			len;

	stick.no_len = 0;
	len = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len < 14000)
	{
		stick.no_len = 1;
		return ;
	}
	dir.x /= len;
	dir.y /= len;
	stick.direction.x = dir.x;
	stick.direction.y = dir.y;
}

void	get_stick_angles(int angle_x, int angle_y, int sign)
{
	static int	x = 0;
	static int	y = 0;

	if (sign == 1)
	{
		if (x != 0 && y != 0)
			calculate_stick_angles(x, y);
		return ;
	}
	if (angle_x != 0)
		x = angle_x;
	if (angle_y != 0)
		y = angle_y;
}

void	controller_sticks(SDL_Event *event, t_keys *keys)
{
	int	angle_x = 0;
	int	angle_y = 0;

	if (event->jaxis.which == 0)
	{
		if (event->jaxis.axis == 2)
			angle_x = event->jaxis.value;
		else if (event->jaxis.axis == 3)
			angle_y = event->jaxis.value;
		else if (event->jaxis.axis == 5)
		{
			if (event->jaxis.value > SHOULDER_DEAD)
				keys->click = 1;
			else if (event->jaxis.value < -SHOULDER_DEAD)
				keys->click = 0;
		}
		else if (event->jaxis.axis == 4)
		{
			if (event->jaxis.value > SHOULDER_DEAD)
				keys->r_key = 1;
			else if (event->jaxis.value < -SHOULDER_DEAD)
				keys->r_key = 0;
		}
		else if (event->jaxis.axis == 0)	//X axis motion
		{
			//Left of dead zone
			if (event->jaxis.value < -STICK_DEATHZONE)
				stick.x_dir_controller = -1;
			//Right of dead zone
			else if (event->jaxis.value > STICK_DEATHZONE)
				stick.x_dir_controller = 1;
			else
				stick.x_dir_controller = 0;
		}
		else if (event->jaxis.axis == 1)	//Y
		{
			//Below of dead zone
			if (event->jaxis.value < -STICK_DEATHZONE)
				stick.y_dir_controller = -1;
			//Above of dead zone
			else if (event->jaxis.value > STICK_DEATHZONE)
				stick.y_dir_controller = 1;
			else
				stick.y_dir_controller = 0;
		}
	}
	get_stick_angles(angle_x, angle_y, 0);
	if (stick.y_dir_controller == 0 && stick.x_dir_controller == 0)
	{
		stick.stick_angle = 1;
		return ;
	}
	stick.stick_angle = atan2((double)stick.y_dir_controller, (double)stick.x_dir_controller) * (180.0 / M_PI);
}
