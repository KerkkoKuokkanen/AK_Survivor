
#include "../top_down.h"

typedef struct	s_game_over
{
	int	death_anim;
	int	seconds;
	int	seen_second;
	int	y_diff;
	int	y_diff_dir;
}				t_game_over;

void	over_updates(int sign, t_game_over *over, t_graphics *all, uint8_t click);
void	init_over(t_game_over *over, t_keys *keys);

void	reset_keys(t_keys *keys)
{
	keys->left = 0;
	keys->right = 0;
	keys->up = 0;
	keys->down = 0;
	keys->click = 0;
	keys->r_key = 0;
	keys->tab = 0;
	keys->escape = 0;
}

void	death_audio(t_audio *audio, t_game_over *over)
{
	if (over->seconds == 0 && over->seen_second != over->seconds)
	{
		Mix_PlayChannel(20, audio->player_death[0], 0);
		Mix_PlayChannel(2, audio->enem_death[0], 0);
	}
	else if (over->seconds == 1 && over->seen_second != over->seconds)
	{
		Mix_PlayChannel(20, audio->player_death[1], 0);
		Mix_PlayChannel(2, audio->enem_death[0], 0);
	}
	else if (over->seconds == 2 && over->seen_second != over->seconds)
	{
		Mix_PlayChannel(20, audio->player_death[2], 0);
		Mix_PlayChannel(2, audio->enem_death[0], 0);
	}
}

void	manage_y_diff(t_game_over *over)
{
	if (over->y_diff_dir == 0)
		over->y_diff++;
	else
		over->y_diff--;
	if (over->y_diff >= 180)
		over->y_diff_dir = 1;
	if (over->y_diff <= 160)
		over->y_diff_dir = 0;
}

void	create_particle(t_textures *text)
{
	t_enemy enem;
	int		i = 0;

	enem.type = 1;
	enem.hbox.w = 2;
	enem.hbox.h = 2;
	while (i < 4)
	{
		enem.hbox.x = CENTER_X;
		enem.hbox.y = CENTER_Y;
		switch (i)
		{
			case 0:
				enem.hbox.x += 20;
				break ;
			case 1:
				enem.hbox.y += 20;
				break ;
			case 2:
				enem.hbox.x -= 20;
				break ;
			case 3:
				enem.hbox.y -= 20;
				break ;
		}
		particle_main(&enem, NULL, NULL, 3);
		i++;
	}
}

void	death_drawing(t_graphics *all, t_player *player, t_textures *text, t_game_over *over)
{
	if (over->seconds == 0)
		return ;
	make_curr_graph(all, text->black_background, NULL, NULL, NULL, 0, 0);
	if (over->seconds < 2)
		make_curr_graph(all, player->anim.idle_dmg, &player->anim.rect, NULL, NULL, 0 , 0);
	if (over->seconds == 2 && over->seen_second != 2)
		create_particle(text);
	put_text_to_screen(all, 240, over->y_diff, "game over", 20, 1);
	if (over->seconds >= 3)
		manage_y_diff(over);
}

int	check_meeting_buttons(SDL_Rect *frame, int x, int y, SDL_Rect dest)
{
	if (point_meeting(x, y, dest))
	{
		frame->x += 32;
		return (1);
	}
	else
		frame->x = 0;
	return (0);
}

int	handle_hit(t_audio *audio, int x, int y, uint8_t click, int hit, int curr, int *hover)
{
	if (hit == 0)
		return (0);
	if (*hover != curr)
	{
		Mix_PlayChannel(23, audio->rollover, 0);
		*hover = curr;
	}
	if (click == 1)
	{
		Mix_PlayChannel(22, audio->button, 0);
		return (1);
	}
	return (0);
}

int	buttons_to_game_over(t_graphics *all, t_audio *audio, t_textures *text, t_game_over *over, uint8_t click, int x, int y, int *hover)
{
	if (over->seconds < 3)
		return (0);
	int			hit = 0;
	int			did_hit = 0;
	SDL_Rect	dest1 = {380, 600, 128, 64};
	SDL_Rect	dest2 = {580, 600, 128, 64};
	SDL_Rect	dest3 = {780, 600, 128, 64};
	SDL_Rect	frame = {0, 0, 32, 16};

	hit = check_meeting_buttons(&frame, x, y, scale_the_rect(dest1));
	if (hit != 0)
		did_hit = 1;
	make_curr_graph(all, text->button, &dest1, &frame, NULL, 0, 0);
	put_text_to_screen(all, 386, 623, "main menu", 3, 1);
	if (handle_hit(audio, x, y, click, hit, 1, hover))
		return (2);
	hit = check_meeting_buttons(&frame, x, y, scale_the_rect(dest2));
	if (hit != 0)
		did_hit = 1;
	make_curr_graph(all, text->button, &dest2, &frame, NULL, 0, 0);
	put_text_to_screen(all, 596, 623, "restart", 3, 1);
	if (handle_hit(audio, x, y, click, hit, 2, hover))
		return (1);
	hit = check_meeting_buttons(&frame, x, y, scale_the_rect(dest3));
	if (hit != 0)
		did_hit = 1;
	make_curr_graph(all, text->button, &dest3, &frame, NULL, 0, 0);
	put_text_to_screen(all, 790, 623, "exit game", 3, 1);
	if (handle_hit(audio, x, y, click, hit, 3, hover))
		exit(0);
	if (did_hit == 0)
		*hover = 0;
	return (0);
}

void	stats_game_over(t_game_over *over, SDL_Renderer *rend)
{
	float	multi = 1;

	if (aspect_ratio == 0)
		multi = 0.9;
	if (over->seconds < 3)
		return ;
	rend_put_text_to_screen(rend, 300, 400 * multi, "enemies killed :", 4, 1);
	rend_put_number_to_screen(rend, enemies_killed_during_game, 700, 400 * multi, 3);
	rend_put_text_to_screen(rend, 300, 500 * multi, "bosses killed :", 4, 1);
	rend_put_number_to_screen(rend, bosses_killed_during_game, 700, 497 * multi, 3);
	rend_put_text_to_screen(rend, 767, 500 * multi, "out of", 4, 1);
	rend_put_number_to_screen(rend, 20, 900, 497 * multi, 3);
}

int	game_over(t_graphics *all, t_textures *text, t_player *player, t_wre *wre, t_audio *audio, t_keys *keys)
{
	clock_t				start;
	clock_t				end;
	static t_game_over	over = {0, 0, (-1), 200, 0};
	int					x, y;
	int					button, hover = 0;

	init_over(&over, keys);
	Mix_HaltChannel(21);
	while (1)
	{
		start = clock();
		SDL_RenderClear(wre->rend);
		ft_keys(wre->event, keys);
		death_audio(audio, &over);
		over_updates(0, &over, all, keys->click);
		death_drawing(all, player, text, &over);
		particle_main(NULL, &text->white_particle, all, (-1));
		stats_game_over(&over, wre->rend);
		button = buttons_to_game_over(all, audio, text, &over, keys->click, x, y, &hover);
		if (button != 0)
			return (button);
		SDL_GetMouseState(&x, &y);
		put_images_to_screen(wre->rend, all);
		lvl_c_to_screen(wre->rend, text->cursor, x, y);
		SDL_RenderPresent(wre->rend);
		end = clock();
		SDL_Delay(figure_the_delay(start, end));
	}
}

void	over_updates(int sign, t_game_over *over, t_graphics *all, uint8_t click)
{
	static int	timer = 0;

	if (sign == START_INIT)
	{
		timer = 0;
		return ;
	}
	if (click == 1)
	{
		over->seconds = 3;
		timer = 0;
	}
	if (over->seconds >= 1)
		clear_screen(all, sizeof(t_graphics) * E_COUNT);
	if ((timer % 60) == 0 && timer != 0)
		over->seconds++;
	else
		over->seen_second = over->seconds;
	timer++;
}

void	init_over(t_game_over *over, t_keys *keys)
{
	over->death_anim = 0;
	over->seconds = 0;
	over->seen_second = (-1);
	over->y_diff = 160;
	over->y_diff_dir = 0;
	normal_particle_blood_life = 100;
	over_updates(START_INIT, NULL, NULL, 0);
	reset_keys(keys);
	particle_main(NULL, NULL, NULL, START_INIT);
}
