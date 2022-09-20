
#include "../top_down.h"
#define	CONFETTI_AMOUNT 10
#define	CONFETTI_LIFE 80

int		count_all_the_alive_enems(t_enemy *enem)
{
	int	i = 0;
	int	count = 0;

	while (i < E_COUNT)
	{
		if (enem[i].type != 0)
			count++;
		i++;
	}
	return (count);
}

int		number_of_enems_to_kill_in_a_frame(t_enemy *enem)
{
	int	alive_amount = count_all_the_alive_enems(enem);
	int	ret;

	ret = alive_amount / 40;
	if ((alive_amount % 40) != 0)
		ret += 1;
	if (ret < 1)
		return (1);
	return (ret);
}

void	victory_screen_enem_handling(t_graphics *all, t_enemy *enem, Mix_Chunk *death, const int kill_number)
{
	int			i = 0;
	int			count = 0;
	static int	kill_time = 0;

	while (i < E_COUNT)
	{
		if (enem[i].type != 0)
		{
			move_dest_from_player(&enem[i].pos);
			enem[i].text.rect.x = enem[i].pos.x;
			enem[i].text.rect.y = enem[i].pos.y;
			update_enem_hbox(&enem[i]);
			if (count < kill_number && kill_time == 0)
			{
				particle_main(&enem[i], NULL, NULL, i);
				enem[i].type = 0;
				Mix_PlayChannel(2, death, 0);
				if (s_shake_active != 2)
					s_shake_active = 1;
				screen_shake_amount = 1;
			}
			else if (place_meeting(enem[i].text.rect, screen))
				ysort(all, enem[i].text.text, &enem[i].text.rect, &enem[i].frame, NULL, 0, enem[i].sign, 0);
			count++;
		}
		i++;
	}
	kill_time += 1;
	if (kill_time == 3)
		kill_time = 0;
}

void	part_enem_init(t_enemy *part)
{
	part->type = 1;
	part->hbox.x = 0;
	part->hbox.y = (-6);
	part->hbox.w = 1;
	part->hbox.h = 1;
}

void	manage_particles(t_graphics *all, t_textures *text, int count)
{
	static int	confetti_time = 0;
	if (count < 141)
	{
		particle_main(NULL, &text->blood, all, (-1));
		confetti_time = 0;
		return ;
	}
	if ((count % 50) != 0 || confetti_time > 4)
		return ;
	t_enemy	part = { 0 };
	int		i = 0;

	normal_particle_blood_life = CONFETTI_LIFE;
	part_enem_init(&part);
	while (i < CONFETTI_AMOUNT)
	{
		part.hbox.x = (128 * i);
		particle_main(&part, NULL, NULL, 1);
		i++;
	}
	confetti_time += 1;
}

void	win_text(t_graphics *all)
{
	int	minute_pos = 702;

	if (lazy_minute_get_variable > 9)
		minute_pos = 675;
	put_text_to_screen(all, 436, 100, "victory", 15, 1);
	put_text_to_screen(all, 280, 300, "enemies killed :", 5, 1);
	put_number_to_screen(all, enemies_killed_during_game, 700, 297, 3);
	put_text_to_screen(all, 280, 400, "total level :", 5, 1);
	put_number_to_screen(all, lvl_up_counter, 700, 397, 3);
	put_text_to_screen(all, 280, 500, "time survived :", 5, 1);
	put_number_to_screen(all, lazy_minute_get_variable, minute_pos, 497, 3);
	put_text_to_screen(all, 725, 498, ":", 5, 1);
	if (lazy_second_get_variable < 10)
	{
		put_number_to_screen(all, 0, 743, 497, 3);
		put_number_to_screen(all, lazy_second_get_variable, 767, 497, 3);
	}
	else
		put_number_to_screen(all, lazy_second_get_variable, 743, 497, 3);
}

void	text_confetti_and_buttons(t_graphics *all, t_textures *text, t_audio *audio, int x, int y, int count)
{
	if (count == 142)
		Mix_PlayChannel(25, audio->escape_victory, 0);
	particle_main(NULL, &text->confetti, all, (-1));
	if (count > 410)
		win_text(all);
}

int		victory_manage_button(SDL_Renderer *rend, t_tex *button, SDL_Rect dest, int x, int y, uint8_t click, t_audio *audio, int curr, int *hover)
{
	SDL_Rect	frame = {0, 0, 32, 16};
	int			ret = 0;

	dest = scale_the_rect(dest);
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

static int	vdid_hit_check(int did_hit, int check)
{
	if (did_hit != 0)
		return (1);
	return (check);
}

void	v_button_text(SDL_Renderer *rend)
{
	float	multi = 1;

	if (aspect_ratio == 0)
		multi = 0.9;
	rend_put_text_to_screen(rend, 505, 723 * multi, "main menu", 3, 1);
	rend_put_text_to_screen(rend, 736, 722 * multi, "exit", 4, 1);
}

int		victory_screen_buttons(SDL_Renderer *rend, t_tex *button, t_audio *audio, uint8_t click, int x, int y, int *hover)
{
	SDL_Rect	menu = {500, 700, 128, 64};
	SDL_Rect	exitb = {700, 700, 128, 64};
	int			ret = 0, did_hit = 0, check = 0;

	if ((did_hit = victory_manage_button(rend, button, menu, x, y, click, audio, 1, hover)) == 2)
		ret = 1;
	check = vdid_hit_check(did_hit, check);
	if ((did_hit = victory_manage_button(rend, button, exitb, x, y, click, audio, 2, hover)) == 2)
		exit(0);
	check = vdid_hit_check(did_hit, check);
	if (check == 0)
		*hover = 0;
	v_button_text(rend);
	return (ret);
}

int		victory_screen(t_graphics *all, t_wre *wre, t_audio *audio, t_textures *text, t_player *player, t_keys *keys, t_enemy *enem)
{
	if (bosses_killed_during_game < 20)
		return (0);
	int		x,y;
	int		count = 0;
	int		hover = 0;
	int		kill_number = number_of_enems_to_kill_in_a_frame(enem);
	clock_t	start, end;

	Mix_HaltChannel(21);	//game music channel
	speed = real_speed;
	while (1)
	{
		start = clock();
		SDL_RenderClear(wre->rend);
		clear_screen(all, sizeof(t_graphics) * SPRITE_AMOUNT);
		manage_screen_shake();
		screen_shaker(&text->g_move.x, &text->g_move.y);
		ft_keys(wre->event, keys);
		SDL_GetMouseState(&x, &y);
		make_curr_graph(all, text->ground, NULL, &text->g_move, NULL, 0, 0);
		move_player(player, *keys, all, &text->g_move, x, audio->walk);
		gun(text->gun, x, y, player->anim.rect, all);
		ysort(all, text->blood, NULL, NULL, NULL, 0, 0, (-1));
		victory_screen_enem_handling(all, enem, audio->enem_death[0], kill_number);
		manage_particles(all, text, count);
		boss_particle(enem, &text->boss_bood, all, (-1));
		if (count > 141)
			text_confetti_and_buttons(all, text, audio, x, y, count);
		put_images_to_screen(wre->rend, all);
		if (count > 410)
		{
			if (victory_screen_buttons(wre->rend, &text->button, audio, keys->click, x, y, &hover) == 1)
				return (1);
		}
		lvl_c_to_screen(wre->rend, text->cursor, x, y);
		SDL_RenderPresent(wre->rend);
		count++;
		end = clock();
		SDL_Delay(figure_the_delay(start, end));
	}
}
