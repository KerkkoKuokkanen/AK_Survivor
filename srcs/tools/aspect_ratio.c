
#include "../top_down.h"

int		round_save(float save)
{
	int	tester = save;

	save -= tester;
	if (save < 0.5)
		return (tester);
	return (tester + 1);
}

SDL_Rect	scale_the_rect(SDL_Rect dest)
{
	if (aspect_ratio == 1)
		return (dest);
	float	save;

	save = (float)dest.y * 0.9;
	dest.y = round_save(save);
	save = (float)dest.h * 0.9;
	dest.h = round_save(save);
	return (dest);
}

void	change_aspect_ratio_in_file(int curr)
{
	int		fd = open("sprites/aspect_ratio.txt", O_WRONLY);
	char	c = curr + '0';

	write(fd, &c, sizeof(char));
	close(fd);
}

void	manage_button_aspect(t_graphics *all, t_textures *text, t_audio *audio, int x, int y, uint8_t click, int curr, int *hover)
{
	static int	curr_aspect = 3;
	static int	sound_check = 0;
	SDL_Rect	frame = {0, 0, 32, 16};
	SDL_Rect	dest = {600, 113, 128, 64};

	if (curr_aspect == 3 && curr_aspect != aspect_ratio)
		curr_aspect = aspect_ratio;
	dest.x += 162 * curr;
	if (curr == curr_aspect)
	{
		frame.x += 32;
		if (point_meeting(x, y, scale_the_rect(dest)))
			*hover = curr;
		make_curr_graph(all, text->button, &dest, &frame, NULL, 0, 0);
		return ;
	}
	if (point_meeting(x, y, scale_the_rect(dest)))
	{
		frame.x += 32;
		if (*hover != curr)
		{
			*hover = curr;
			Mix_PlayChannel(23, audio->rollover, 0);
		}
		if (click == 1 && sound_check != 1)
		{
			Mix_PlayChannel(22, audio->button, 0);
			curr_aspect = curr;
			change_aspect_ratio_in_file(curr);
		}
	}
	else
		*hover = 2;
	sound_check = click;
	make_curr_graph(all, text->button, &dest, &frame, NULL, 0, 0);
}

void	aspect_button_text(t_graphics *all)
{
	put_number_to_screen(all, 16, 625, 132, 3);
	put_text_to_screen(all, 670, 135, ":", 4, 1);
	put_number_to_screen(all, 9, 685, 132, 3);
	put_number_to_screen(all, 16, 777, 132, 3);
	put_text_to_screen(all, 823, 135, ":", 4, 1);
	put_number_to_screen(all, 10, 837, 132, 3);
}

void	audio_menu_screen_aspect_ratio(t_graphics *all, t_textures *text, t_audio *audio, int x, int y, uint8_t click, int *hover)
{
	put_text_to_screen(all, 217, 130, "aspect ratio :", 6, 1);
	put_text_to_screen(all, 265, 70, "if you want the aspect ratio to change: restart the game", 3, 1);
	manage_button_aspect(all, text, audio, x, y, click, 0, hover);
	manage_button_aspect(all, text, audio, x, y, click, 1, hover);
	aspect_button_text(all);
}

void	change_window_value(SDL_Window *win)
{
	if (window_check_value == 0)
		window_check_value = 1;
	else
		window_check_value = 0;
	char	c = window_check_value + '0';
	int		fd = open("sprites/window.txt", O_WRONLY);
	write(fd, &c, sizeof(char));
	close(fd);
	SDL_SetWindowFullscreen(win, window_check_value);
}

void	full_screen_button(t_graphics *all, t_textures *text, t_audio *audio, int x, int y, uint8_t *click, t_wre *wre)
{
	SDL_Rect	dest = {762, 475, 128, 64};
	SDL_Rect	frame = {0, 0, 32, 16};
	static int	hover = 0;
	static int	click_check = 1;
	static int	stay = 0;

	if (stay == 1)
	{
		if (*click == 0)
		{
			stay = 0;
			Mix_PlayChannel(22, audio->button, 0);
			change_window_value(wre->win);
		}
	}
	if (point_meeting(x, y, scale_the_rect(dest)))
	{
		frame.x += 32;
		if (hover != 1)
		{
			hover = 1;
			Mix_PlayChannel(23, audio->rollover, 0);
		}
		if (*click == 1 && click_check == 0)
			stay = 1;
		click_check = *click;
	}
	else
		hover = 0;
	make_curr_graph(all, text->button, &dest, &frame, NULL, 0, 0);
}

void	full_screen(t_graphics *all, t_wre *wre, t_textures *text, t_audio *audio, int x, int y, uint8_t *click)
{
	put_text_to_screen(all, 235, 490, "fullscreen :", 6, 1);
	full_screen_button(all, text, audio, x, y, click, wre);
	if (window_check_value == 1)
		put_text_to_screen(all, 639 + 162, 494, "on", 5, 1);
	else
		put_text_to_screen(all, 628 + 162, 494, "off", 5, 1);
}
