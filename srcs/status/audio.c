
#include "../top_down.h"

void	manage_volume()
{
	float	gv = 0.125 * global_game_volume;
	float	mv = 0.125 * global_music_volume;

	Mix_Volume(0, MIX_MAX_VOLUME * gv);	//getting lvl
	Mix_Volume(1, MIX_MAX_VOLUME * gv);	//choosing card
	Mix_Volume(2, 10 * gv);				//enemy death
	Mix_Volume(3, MIX_MAX_VOLUME * gv);	//hurt sound
	Mix_Volume(4, 20 * gv);				//hitmarks
	Mix_Volume(5, 48 * gv);				//shots
	Mix_Volume(6, 20 * gv);				//orbs
	Mix_Volume(7, 64 * gv);				//walking
	Mix_Volume(8, 20 * gv);				//reload
	Mix_Volume(9, 40 * gv);				//shock effect
	Mix_Volume(10, MIX_MAX_VOLUME * gv);	//boss spawn
	Mix_Volume(11, 50 * gv);				//rage
	Mix_Volume(12, 120 * gv);			//flame burst
	Mix_Volume(13, 90 * gv);				//egg crack
	Mix_Volume(14, 8 * gv);				//acid hit
	Mix_Volume(15, 25 * gv);				//dead whale explosion
	Mix_Volume(16, 40 * gv);				//dagger woosh
	Mix_Volume(17, 20 * gv);				//critical hit
	Mix_Volume(18, 85 * gv);				//dark aura
	Mix_Volume(19, 80 * gv);				//rage and dark flameburst
	Mix_Volume(20, 100 * gv);			//death impale
	Mix_Volume(21, (60 * mv));				//music // 60
	Mix_Volume(22, 100 * gv);				//button
	Mix_Volume(23, 25 * gv);				//roll over
	Mix_Volume(24, 25 * mv);				//menu music
	Mix_Volume(25, 60 * mv);				//victory music
}

int		back_button(t_graphics *all, int x, int y, uint8_t click, t_tex *button, t_audio *audio, int *hover)
{
	SDL_Rect	dest = {1060, 670, 128, 64};
	SDL_Rect	frame = {0, 0, 32, 16};
	static int	check = 0;

	if (point_meeting(x, y, scale_the_rect(dest)))
	{
		frame.x = 32;
		if (*hover == 0)
			Mix_PlayChannel(23, audio->rollover, 0);
		*hover = 1;
	}
	else
		*hover = 0;
	make_curr_graph(all, *button, &dest, &frame, NULL, 0, 0);
	put_text_to_screen(all, 1085, 691, "back", 4, 1);
	if (frame.x != 0 && click == 1 && check != click)
	{
		Mix_PlayChannel(22, audio->button, 0);
		return (1);
	}
	check = click;
	return (0);
}

void	audio_screen_text(t_graphics *all)
{
	put_text_to_screen(all, 200, 250, "music  volume :", 6, 1);
	put_text_to_screen(all, 212, 370, "game  volume :", 6, 1);
}

void	draw_audio_bar(t_graphics *all, t_tex *bar, t_tex *fill)
{
	SDL_Rect	dest1 = {600, 259, 400, 10};
	SDL_Rect	dest2 = {600, 379, 400, 10};
	SDL_Rect	dest_fill1 = {600, 259, 0, 10};
	SDL_Rect	dest_fill2 = {600, 379, 0, 10};

	make_curr_graph(all, *bar, &dest1, NULL, NULL, 0, 0);
	make_curr_graph(all, *bar, &dest2, NULL, NULL, 0, 0);
	dest_fill1.w = 50 * global_music_volume;
	dest_fill2.w = 50 * global_game_volume;
	make_curr_graph(all, *fill, &dest_fill1, NULL, NULL, 0, 0);
	make_curr_graph(all, *fill, &dest_fill2, NULL, NULL, 0, 0);
}

int	draw_indicator_to_bars(t_graphics *all, t_tex *indicator, int x, int y, uint8_t click)
{
	static SDL_Rect	dest1 = {590, 237, 20, 54};
	static SDL_Rect	dest2 = {590, 357, 20, 54};
	int				x1, x2;
	int				ret = 0;

	x1 = (50 * global_music_volume);
	x2 = (50 * global_game_volume);
	dest1.x += x1;
	dest2.x += x2;
	bigger_smaller_indicator(&dest1, &dest2, x, y, 0);
	make_curr_graph(all, *indicator, &dest1, NULL, NULL, 0, 0);
	make_curr_graph(all, *indicator, &dest2, NULL, NULL, 0, 0);
	if (point_meeting(x, y, scale_the_rect(dest1)) && click == 1)
		ret = 1;
	else if (point_meeting(x, y, scale_the_rect(dest2)) && click == 1)
		ret = 2;
	dest1.x -= x1;
	dest2.x -= x2;
	return (ret);
}

int	find_the_right_box(int x)
{
	const static int	xrange[9] = {573, 623, 673, 723, 773, 823, 873, 923, 973};

	if (x > xrange[8])
		return (8);
	if (x > xrange[7])
		return (7);
	if (x > xrange[6])
		return (6);
	if (x > xrange[5])
		return (5);
	if (x > xrange[4])
		return (4);
	if (x > xrange[3])
		return (3);
	if (x > xrange[2])
		return (2);
	if (x > xrange[1])
		return (1);
	return (0);
}

void	update_volumes_to_file(int	sign)
{
	int		fd;
	char	c;

	if (sign == 1)
	{
		c = global_music_volume + '0';
		fd = open("game_audio/volume/music.txt", O_WRONLY);
		write(fd, &c, sizeof(char));
	}
	else if (sign == 2)
	{
		c = global_game_volume + '0';
		fd = open("game_audio/volume/game.txt", O_WRONLY);
		write(fd, &c, sizeof(char));
	}
	close(fd);
}

void	audio_indicator_drag(int x, int drag_active, uint8_t click, t_audio *audio)
{
	static int	click_active = 0;
	int			save1 = global_music_volume, save2 = global_game_volume;

	if (drag_active == 0 && click_active == 0)
		return ;
	if (drag_active == 1)
		click_active = 1;
	else if (drag_active == 2)
		click_active = 2;
	if ((click_active == 1 || click_active == 2) && click == 0)
	{
		click_active = 0;
		return ;
	}
	if (click_active == 1)
		global_music_volume = find_the_right_box(x);
	else if (click_active == 2)
		global_game_volume = find_the_right_box(x);
	if (save1 != global_music_volume || save2 != global_game_volume)
		Mix_PlayChannel(23, audio->rollover, 0);
	manage_volume();
	update_volumes_to_file(click_active);
}

void	audio_slider(t_graphics *all, t_textures *text, t_audio *audio, int x, int y, uint8_t click)
{
	static int	drag_active = 0;

	draw_audio_bar(all, &text->audio_bar_remain, &text->audio_bar);
	drag_active = draw_indicator_to_bars(all, &text->audio_slider, x, y, click);
	audio_indicator_drag(x, drag_active, click, audio);
}

int		audio_menu(t_graphics *all, int x, int y, uint8_t click, t_textures *text, t_audio *audio)
{
	static int	back_button_hover = 0;
	static int	aspect_button_hover = 0;

	audio_screen_text(all);
	audio_slider(all, text, audio, x, y, click);
	audio_menu_screen_aspect_ratio(all, text, audio, x, y, click, &aspect_button_hover);
	if (back_button(all, x, y, click, &text->button, audio, &back_button_hover))
	{
		back_button_hover = 0;
		aspect_button_hover = 0;
		return (0);
	}
	return (2);
}

int		rend_back_button(SDL_Renderer *rend, int x, int y, uint8_t click, t_tex *button, t_audio *audio, int *hover)
{
	SDL_Rect	dest = {1060, 670, 128, 64};
	SDL_Rect	frame = {0, 0, 32, 16};
	int			nbutton = 691;

	dest = scale_the_rect(dest);
	if (aspect_ratio != 1)
		nbutton *= 0.9;
	if (point_meeting(x, y, dest))
	{
		frame.x = 32;
		if (*hover == 0)
			Mix_PlayChannel(23, audio->rollover, 0);
		*hover = 1;
	}
	else
		*hover = 0;
	SDL_RenderCopy(rend, button->text, &frame, &dest);
//	make_curr_graph(all, *button, &dest, &frame, NULL, 0, 0);
	rend_put_text_to_screen(rend, 1085, nbutton, "back", 4, 1);
	if (frame.x != 0 && click == 1)
	{
		Mix_PlayChannel(22, audio->button, 0);
		return (1);
	}
	return (0);
}

void	rend_audio_screen_text(SDL_Renderer *rend)
{
	rend_put_text_to_screen(rend, 200, 250, "music  volume :", 6, 1);
	rend_put_text_to_screen(rend, 212, 370, "game  volume :", 6, 1);
}

void	rend_draw_audio_bar(SDL_Renderer *rend, t_tex *bar, t_tex *fill)
{
	SDL_Rect	dest1 = {600, 259, 400, 10};
	SDL_Rect	dest2 = {600, 379, 400, 10};
	SDL_Rect	dest_fill1 = {600, 259, 0, 10};
	SDL_Rect	dest_fill2 = {600, 379, 0, 10};

	SDL_RenderCopy(rend, bar->text, NULL, &dest1);
	SDL_RenderCopy(rend, bar->text, NULL, &dest2);
//	make_curr_graph(all, *bar, &dest1, NULL, NULL, 0, 0);
//	make_curr_graph(all, *bar, &dest2, NULL, NULL, 0, 0);
	dest_fill1.w = 50 * global_music_volume;
	dest_fill2.w = 50 * global_game_volume;
	SDL_RenderCopy(rend, fill->text, NULL, &dest_fill1);
	SDL_RenderCopy(rend, fill->text, NULL, &dest_fill2);
//	make_curr_graph(all, *fill, &dest_fill1, NULL, NULL, 0, 0);
//	make_curr_graph(all, *fill, &dest_fill2, NULL, NULL, 0, 0);
}

int	rend_draw_indicator_to_bars(SDL_Renderer *rend, t_tex *indicator, int x, int y, uint8_t click)
{
	static SDL_Rect	dest1 = {590, 237, 20, 54};
	static SDL_Rect	dest2 = {590, 357, 20, 54};
	int				x1, x2;
	int				ret = 0;

	x1 = (50 * global_music_volume);
	x2 = (50 * global_game_volume);
	dest1.x += x1;
	dest2.x += x2;
	rend_bigger_smaller_indicator(&dest1, &dest2, x, y, 0);
	SDL_RenderCopy(rend, indicator->text, NULL, &dest1);
	SDL_RenderCopy(rend, indicator->text, NULL, &dest2);
//	make_curr_graph(all, *indicator, &dest1, NULL, NULL, 0, 0);
//	make_curr_graph(all, *indicator, &dest2, NULL, NULL, 0, 0);
	if (point_meeting(x, y, dest1) && click == 1)
		ret = 1;
	else if (point_meeting(x, y, dest2) && click == 1)
		ret = 2;
	dest1.x -= x1;
	dest2.x -= x2;
	return (ret);
}

void	rend_audio_slider(SDL_Renderer *rend, t_textures *text, t_audio *audio, int x, int y, uint8_t click)
{
	static int	drag_active = 0;

	rend_draw_audio_bar(rend, &text->audio_bar_remain, &text->audio_bar);
	drag_active = rend_draw_indicator_to_bars(rend, &text->audio_slider, x, y, click);
	audio_indicator_drag(x, drag_active, click, audio);
}

int		rend_audio_menu(SDL_Renderer *rend, int x, int y, uint8_t click, t_textures *text, t_audio *audio)
{
	static int	back_button_hover = 0;

	rend_audio_screen_text(rend);
	rend_audio_slider(rend, text, audio, x, y, click);
	if (rend_back_button(rend, x, y, click, &text->button, audio, &back_button_hover))
	{
		back_button_hover = 0;
		return (0);
	}
	return (2);
}
