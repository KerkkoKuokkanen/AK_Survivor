
#include "../top_down.h"
#define GROUND_TO_TOP_LEFT 2

void	ground_scroll_anim(t_graphics *all, t_tex ground)
{
	static SDL_Rect	frame = {0, 0, GW, GH};

	ground_scroll(GROUND_TO_TOP_LEFT, 1, &frame);
	make_curr_graph(all, ground, NULL, &frame, NULL, 0, 0);
}

void	title_screen(t_graphics *all)
{
	put_text_to_screen(all, 330, 192, "ak survivor", 14, 1);
	put_text_to_screen(all, 548, 280, "kill all bosses", 3, 1);
	put_text_to_screen(all, 603, 371, "play", 4, 1);
	put_text_to_screen(all, 588, 454, "settings", 3, 1);
	put_text_to_screen(all, 611, 531, "exit", 4, 1);
}

int		manage_button(t_graphics *all, t_tex *button, SDL_Rect dest, int x, int y, uint8_t click, t_audio *audio, int curr, int *hover)
{
	SDL_Rect	frame = {0, 0, 32, 16};
	int			ret = 0;

	if (point_meeting(x, y, scale_the_rect(dest)))
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
		make_curr_graph(all, *button, &dest, &frame, NULL, 0 , 0);
	return (ret);
}

static int	did_hit_checker(int did_hit, int check)
{
	if (did_hit != 0)
		return (1);
	return (check);
}

int		button_text_to_main_menu(t_graphics *all, t_textures *text, int x, int y, uint8_t click, t_audio *audio, int *h_main)
{
	SDL_Rect	game = {576, 350, 128, 64};
	SDL_Rect	audiob = {576, 430, 128, 64};
	SDL_Rect	exitb = {576, 510, 128, 64};
	int			ret = 0, did_hit = 0, check = 0;

	if ((did_hit = manage_button(all, &text->button, game, x, y, click, audio, 1, h_main)) == 2)
		ret = 1;
	check = did_hit_checker(did_hit, check);
	if ((did_hit = manage_button(all, &text->button, audiob, x, y, click, audio, 2, h_main)) == 2)
		ret = 2;
	check = did_hit_checker(did_hit, check);
	if ((did_hit = manage_button(all, &text->button, exitb, x, y, click, audio, 3, h_main)) == 2)
		exit(0);
	check = did_hit_checker(did_hit, check);
	if (check == 0)
		*h_main = 0;
	return (ret);
}

void	main_menu(t_wre *wre, t_graphics *all, t_textures *text, t_audio *audio, t_keys *keys)
{
	int		x, y;
	clock_t	start, end;
	int		bool = 0;
	int		h_main = 0;

	while (1)
	{
		start = clock();
		SDL_RenderClear(wre->rend);
		clear_screen(all, sizeof(t_graphics) * SPRITE_AMOUNT);
		ft_keys(wre->event, keys);
		get_menu_x_and_y(&x, &y);
//		SDL_GetMouseState(&x, &y);
		ground_scroll_anim(all, text->ground);
		put_text_to_screen(all, 1100, 780, "game by:  k kuokkanen", 2, 1);
		if (bool != 2)
		{
			if ((bool = button_text_to_main_menu(all, text, x, y, keys->click, audio, &h_main)) == 1)
				break ;
			title_screen(all);
			if (bool == 2)
				bigger_smaller_indicator(NULL, NULL, 0, 0, 1);
		}
		else
		{
			full_screen(all, wre, text, audio, x, y, &keys->click);
			bool = audio_menu(all, x, y, keys->click, text, audio);
		}
		put_images_to_screen(wre->rend, all);
		lvl_c_to_screen(wre->rend, text->cursor, x, y);
		SDL_RenderPresent(wre->rend);
		end = clock();
		SDL_Delay(figure_the_delay(start, end));
	}
	SDL_RenderClear(wre->rend);
	clear_screen(all, sizeof(t_graphics) * SPRITE_AMOUNT);
}
