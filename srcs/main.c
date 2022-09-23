
#include "top_down.h"

void	cursor_to_screen(SDL_Renderer *rend, t_tr cursor, int x, int y)
{
	if (stick.no_controller == 0)
	{
		x = 640 - (stick.direction.x * 200.f);
		y = P_POS_Y - (stick.direction.y * 200.f);
	}
	cursor.rect.x = x - 7;
	cursor.rect.y = y - 7;
	SDL_RenderCopy(rend, cursor.text.text, NULL, &cursor.rect);
}

void	lvl_c_to_screen(SDL_Renderer *rend, t_tr cursor, int x, int y)
{
	cursor.rect.x = x - 7;
	cursor.rect.y = y - 7;
	SDL_RenderCopy(rend, cursor.text.text, NULL, &cursor.rect);
}

//tried to make the code cleaner by calling these two functions from here
void	p_actions(int x, int y, t_graphics *all, t_player *player, t_keys keys, t_textures *text, Mix_Chunk **walk)
{
	move_player(player, keys, all, &text->g_move, x, walk);
	gun(text->gun, x, y, player->anim.rect, all);
}

void	get_menu_x_and_y(int *x, int *y)
{
	static int	x_center = CENTER_X;
	static int	y_center = 308;
	int			tempx, tempy;
	float		multi = 1;

	if (aspect_ratio == 0)
		multi = 0.9;
	if (stick.no_controller == 0)
	{
		if (stick.no_len == 1)
			return ;
		tempx = x_center - stick.direction.x * 10;
		tempy = y_center - stick.direction.y * 10;
		if (tempx > 0 && tempx < 1280)
		{
			*x = tempx;
			x_center = tempx;
		}
		if (tempy > 0 && tempy < (800 * multi))
		{
			*y = tempy;
			y_center = tempy;
		}
		return ;
	}
	SDL_GetMouseState(x, y);
}

void	get_x_and_y(int *x, int *y)
{
	if (stick.no_controller == 0)
	{
		*x = 640 - (stick.direction.x * 200.f);
		*y = P_POS_Y - (stick.direction.y * 200.f);
		return ;
	}
	SDL_GetMouseState(x, y);
}

// the main while loop for the game. the whole game happens here
// make boss faster with time
int	game(t_wre wre, t_player player, t_textures text, t_audio audio, t_keys keys, t_graphics *all)
{
	t_enemy		*enem = enem_init();
	clock_t		start, end;
	uint8_t		bool = 0;
	int			x, y;

	while (1)
	{
		start = clock();
		ft_keys(wre.event, &keys);
		SDL_RenderClear(wre.rend);
		updates(all, text.ground, text.g_move);
		get_x_and_y(&x, &y);
		boss_spawner(enem, &text.enemy, all, (-1), 0);
		dark_aura_main(enem, &text, &audio, all);
		p_actions(x, y, all, &player, keys, &text, audio.walk);
		creep_main(enem, all, &audio);
		orb_main(enem, all, &text.orb, audio.coin, (-2));
		enemy_main(enem, text.enemy, all);
		egg_main(NULL, all, 0);
		ysort(all, text.blood, NULL, NULL, NULL, 0, 0, (-1));
		bullets_main(x, y, &keys.click, all, &text.bullet, enem,
						audio.gun_shoot, audio.hit, audio.enem_death, &text.mag,
						&keys.r_key, &text.reload_full, &text.reload_empty, audio.gun_reload);
		particle_main(enem, &text.blood, all, (-1));
		boss_particle(enem, &text.boss_bood, all, (-1));
		shock_the_enemies(enem, all, audio.enem_death[0], 0, 0);
		dead_whale_explosion_main(enem, 0, all, 1, &audio, &text.explosion);
		dagger_main(enem, (-1), all, &text, &audio);
		arrow_to_egg(all);
		if ((bool = health_main(&text.health, all, audio.hurt, 0)) == DEATH_OF_PLAYER)
			break ;
		draw_bar(all, text.lvl.bar[0], text.lvl.bar[1]);
		time_main(0, all, &text.nums, &text.dots, 1);
		put_images_to_screen(wre.rend, all);
		lvl_c_to_screen(wre.rend, text.cursor, x, y);
		SDL_RenderPresent(wre.rend);
		show_player_status(all, wre.rend, &keys, &text, &text.cursor);
		if (pause_menu(all, &wre, &text, &audio, &keys) == 3)
			return (0);
		level_up_main(&text.lvl, 0, wre.rend, &text.cursor, &keys, &audio.lvl, all, 0);
		if (victory_screen(all, &wre, &audio, &text, &player, &keys, enem) == 1)
			return (0);
		end = clock();
		SDL_Delay(figure_the_delay(start, end));
	}
	return (game_over(all, &text, &player, &wre, &audio, &keys));
}

void	main_loop(t_wre wre, t_player player, t_textures text, t_audio audio)
{
	t_keys		keys = init_keys();
	int			tru;
	t_graphics	all[SPRITE_AMOUNT];

	clear_screen(all, sizeof(t_graphics) * SPRITE_AMOUNT);
	while (1)
	{
		ft_keys(wre.event, &keys);
		Mix_PlayChannel(24, audio.menu_music, 200000);
		main_menu(&wre, all, &text, &audio, &keys);
		Mix_PlayChannel(1, card_choosing_soundeffect, 0);
		Mix_HaltChannel(24);
		tru = 1;
		while (tru == 1)
		{
			reset_keys(&keys);
			pre_game(NULL);
			Mix_PlayChannel(21, music_audio_file, 20000);
			tru = game(wre, player, text, audio, keys, all);
		}
	}
}

//simple main just some init stuff
int main()
{
	t_wre		wre;
	t_player	player;
	t_textures	text;
	t_audio		audio;

	init(&wre, &player, &text, &audio);
	pre_game(NULL);
	main_loop(wre, player, text, audio);
}

//miselanious function where we handle some simple updates:
//draw ground
//calculate the time
//manage screen shake
void	updates(t_graphics *all, t_tex ground, SDL_Rect g_move)
{
	static int	sec = 0;
	int			time = 0;

	clear_screen(all, sizeof(t_graphics) * SPRITE_AMOUNT);
	manage_screen_shake();
	screen_shaker(&g_move.x, &g_move.y);
	make_curr_graph(all, ground, NULL, &g_move, NULL, 0, 0);
	sec++;
	if (sec == 60)
	{
		sec = 0;
		time = 1;
		all_seconds += 1;
	}
	time_main(time, NULL, NULL, NULL, 0);
}
