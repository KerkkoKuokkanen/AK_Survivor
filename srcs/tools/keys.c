
#include "../top_down.h"

// assign init values for keys struct
t_keys	init_keys()
{
	t_keys keys;

	keys.left = 0;
	keys.right = 0;
	keys.up = 0;
	keys.down = 0;
	keys.click = 0;
	keys.r_key = 0;
	keys.tab = 0;
	keys.escape = 0;
	return (keys);
}

// function for the SDL pollevent where we get the keyimputs of a player
void	ft_keys(SDL_Event event, t_keys *keys)
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
					keys->click = 1;
				break ;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
					keys->click = 0;
				break ;
			case SDL_JOYAXISMOTION:
				controller_sticks(&event, keys);
				break ;
			case SDL_JOYBUTTONDOWN:
				switch (event.jbutton.button)
				{
					case SDL_CONTROLLER_BUTTON_A:
						keys->click = 1;
						break ;
					case SDL_CONTROLLER_BUTTON_START:
						keys->escape = 1;
						break ;
					case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
						keys->tab = 1;
						break ;
					case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
						keys->click = 1;
						break ;
					case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
						dpad_used[0] = 1;
						keys->down = 1;
						break ;
					case SDL_CONTROLLER_BUTTON_DPAD_UP:
						dpad_used[1] = 1;
						keys->up = 1;
						break ;
					case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
						dpad_used[2] = 1;
						keys->left = 1;
						break ;
					case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
						dpad_used[3] = 1;
						keys->right = 1;
						break ;
					case SDL_CONTROLLER_BUTTON_X:
						keys->r_key = 1;
						break ;
					case SDL_CONTROLLER_BUTTON_BACK:
						keys->escape = 1;
						break ;
				}
				break ;
			case SDL_JOYBUTTONUP:
				switch (event.jbutton.button)
				{
					case SDL_CONTROLLER_BUTTON_A:
						keys->click = 0;
						break ;
					case SDL_CONTROLLER_BUTTON_START:
						keys->escape = 0;
						break ;
					case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
						keys->tab = 0;
						break ;
					case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
						keys->click = 0;
						break ;
					case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
						dpad_used[0] = 0;
						keys->down = 0;
						break ;
					case SDL_CONTROLLER_BUTTON_DPAD_UP:
						dpad_used[1] = 0;
						keys->up = 0;
						break ;
					case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
						dpad_used[2] = 0;
						keys->left = 0;
						break ;
					case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
						dpad_used[3] = 0;
						keys->right = 0;
						break ;
					case SDL_CONTROLLER_BUTTON_X:
						keys->r_key = 0;
						break ;
					case SDL_CONTROLLER_BUTTON_BACK:
						keys->escape = 0;
						break ;
				}
				break ;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
						if (keys->escape == 0)
							keys->escape = 1;
						break ;
					case SDL_SCANCODE_A:
						keys->left = 1;
						break ;
					case SDL_SCANCODE_D:
						keys->right = 1;
						break ;
					case SDL_SCANCODE_W:
						keys->up = 1;
						break ;
					case SDL_SCANCODE_S:
						keys->down = 1;
						break ;
					case SDL_SCANCODE_R:
						keys->r_key = 1;
						break ;
					case SDL_SCANCODE_E:
						keys->r_key = 1;
						break ;
					case SDL_SCANCODE_TAB:
						keys->tab = 1;
						break ;
				}
				break ;
			case SDL_KEYUP:
				switch (event.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
						keys->escape = 0;
						break ;
					case SDL_SCANCODE_A:
						keys->left = 0;
						break ;
					case SDL_SCANCODE_D:
						keys->right = 0;
						break ;
					case SDL_SCANCODE_W:
						keys->up = 0;
						break ;
					case SDL_SCANCODE_S:
						keys->down = 0;
						break ;
					case SDL_SCANCODE_R:
						keys->r_key = 0;
						break ;
					case SDL_SCANCODE_E:
						keys->r_key = 0;
						break ;
					case SDL_SCANCODE_TAB:
						keys->tab = 0;
						break ;
				}
				break ;
			break ;
		}
	}
	if (dpad_used[0] == 0 && dpad_used[1] == 0 && dpad_used[2] == 0 && dpad_used[3] == 0)
		stick_to_keys(keys);
	get_stick_angles(0, 0, 1);
}
