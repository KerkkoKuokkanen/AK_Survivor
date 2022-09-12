
#include "../top_down.h"

int		pause_manage_button(SDL_Renderer *rend, t_tex *button, SDL_Rect dest, int x, int y, uint8_t click, t_audio *audio, int curr, int *hover)
{
	SDL_Rect	frame = {0, 0, 32, 16};
	int			ret = 0;

	if (point_meeting(x, y, dest))
	{
		ret = 1;
		if (*hover != curr)
		{
			*hover = curr;
			Mix_PlayChannel(23, audio->rollover, 0);
		}
		frame.x = 32;
		if (click == 1)
		{
			Mix_PlayChannel(22, audio->button, 0);
			ret = 2;
		}
	}
	if (button != NULL)
		SDL_RenderCopy(rend, button->text, &frame, &dest);
	return (ret);
}

static int	did_hit_check(int did_hit, int check)
{
	if (did_hit != 0)
		return (1);
	return (check);
}

void	button_text(SDL_Renderer *rend)
{
	rend_put_text_to_screen(rend, 594, 393, "resume", 3, 1);
	rend_put_text_to_screen(rend, 597, 471, "audio", 4, 1);
	rend_put_text_to_screen(rend, 581, 553, "main menu", 3, 1);
	rend_put_text_to_screen(rend, 611, 631, "exit", 4, 1);
}

int	buttons_to_screen(SDL_Renderer *rend, t_textures *text, t_audio *audio, int x, int y, uint8_t click, int *hover)
{
	SDL_Rect	resume = {576, 370, 128, 64};
	SDL_Rect	audiob = {576, 450, 128, 64};
	SDL_Rect	menub = {576, 530, 128, 64};
	SDL_Rect	exitb = {576, 610, 128, 64};
	int			ret = 0, did_hit = 0, check = 0;

	if ((did_hit = pause_manage_button(rend, &text->button, resume, x, y, click, audio, 1, hover)) == 2)
		ret = 1;
	check = did_hit_check(did_hit, check);
	if ((did_hit = pause_manage_button(rend, &text->button, audiob, x, y, click, audio, 2, hover)) == 2)
		ret = 2;
	check = did_hit_check(did_hit, check);
	if ((did_hit = pause_manage_button(rend, &text->button, menub, x, y, click, audio, 3, hover)) == 2)
		ret = 3;
	check = did_hit_check(did_hit, check);
	if ((did_hit = pause_manage_button(rend, &text->button, exitb, x, y, click, audio, 4, hover)) == 2)
		exit(0);
	check = did_hit_check(did_hit, check);
	if (check == 0)
		*hover = 0;
	button_text(rend);
	return (ret);
}

int		pause_menu(t_graphics *all, t_wre *wre, t_textures *text, t_audio *audio, t_keys *keys)
{
	if (keys->escape != 1)
		return (0);
	clock_t	start, end;
	int		x, y;
	int		hover = 0, ret = 0;

	if (keys->escape == 1)
		keys->escape = 2;
	Mix_Pause(21);
	while (1)
	{
		start = clock();
		SDL_RenderClear(wre->rend);
		put_images_to_screen(wre->rend, all);
		SDL_RenderCopy(wre->rend, text->off_color_status.text, NULL, NULL);
		if (ret == 0)
		{
			rend_put_text_to_screen(wre->rend, 460, 200, "pause", 15, 1);
			ret = buttons_to_screen(wre->rend, text, audio, x, y, keys->click, &hover);
		}
		else if (ret == 2)
			ret = rend_audio_menu(wre->rend, x, y, keys->click, text, audio);
		if (ret == 1 || ret == 3 || keys->escape == 1)
			break ;
		SDL_GetMouseState(&x, &y);
		ft_keys(wre->event, keys);
		lvl_c_to_screen(wre->rend, text->cursor, x, y);
		SDL_RenderPresent(wre->rend);
		end = clock();
		SDL_Delay(figure_the_delay(start, end));
	}
	reset_keys(keys);
	if (keys->escape == 1)
		keys->escape = 2;
	if (ret == 1 || ret == 0)
		Mix_Resume(21);
	return (ret);
}