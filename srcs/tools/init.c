
#include "../top_down.h"

// init run anim
void	run_init(t_player *player)
{
	player->anim.run[0].x = 0;
	player->anim.run[0].y = 0;
	player->anim.run[0].w = 32;
	player->anim.run[0].h = 32;
	player->anim.run[1].x = 32;
	player->anim.run[1].y = 0;
	player->anim.run[1].w = 32;
	player->anim.run[1].h = 32;
	player->anim.run[2].x = 64;
	player->anim.run[2].y = 0;
	player->anim.run[2].w = 32;
	player->anim.run[2].h = 32;
	player->anim.run[3].x = 96;
	player->anim.run[3].y = 0;
	player->anim.run[3].w = 32;
	player->anim.run[3].h = 32;
	player->anim.run[4].x = 128;
	player->anim.run[4].y = 0;
	player->anim.run[4].w = 32;
	player->anim.run[4].h = 32;
	player->anim.run[5].x = 160;
	player->anim.run[5].y = 0;
	player->anim.run[5].w = 32;
	player->anim.run[5].h = 32;
}

// init values and SDL_Rects
void	rects(t_textures *text)
{
	int	i = 0;
	text->enemy.zomb.rect.w = 64;
	text->enemy.zomb.rect.h = 64;
	text->enemy.red_enemy.rect.w = 64;
	text->enemy.red_enemy.rect.h = 64;
	text->enemy.annoying_enemy.rect.w = 32; //may need change
	text->enemy.annoying_enemy.rect.h = 64;
	text->enemy.boss.rect.w = 192;
	text->enemy.boss.rect.h = 180;
	text->enemy.pentagram.rect.w = 360;
	text->enemy.pentagram.rect.h = 360;
	text->enemy.brown_enem.rect.w = 80;
	text->enemy.brown_enem.rect.h = 80;
	text->enemy.crab.rect.w = 300;
	text->enemy.crab.rect.h = 120;
	text->enemy.minotaur.rect.w = 270;
	text->enemy.minotaur.rect.h = 225;
	text->enemy.red_frog.rect.w = 209;
	text->enemy.red_frog.rect.h = 204;
	text->enemy.scorpion.rect.w = 228;
	text->enemy.scorpion.rect.h = 186;
	text->enemy.flame.rect.w = 240;
	text->enemy.flame.rect.h = 240;
	pentagram_frame.w = 360;
	pentagram_frame.h = 360;
	pentagram_frame.y = 0;
	text->shot.rect.w = 700;
	text->shot.rect.h = 10;
	text->s_sheet.w = 700;
	text->s_sheet.h = 10;
	text->gun.rect.x = P_POS_X - 5;
	text->gun.rect.y = P_POS_Y + 22;
	text->gun.rect.w = 54;
	text->gun.rect.h = 54;
	text->cursor.rect.w = 14;
	text->cursor.rect.h = 14;
	text->g_move.x = 0;
	text->g_move.y = 0;
	text->g_move.w = GW;
	text->g_move.h = GH;
	text->lvl.bar[0].rect.x = 240;
	text->lvl.bar[0].rect.y = 770;
	text->lvl.bar[0].rect.h = 10;
	text->lvl.bar[0].rect.w = 0;
	text->lvl.bar[1].rect.x = 240;
	text->lvl.bar[1].rect.y = 770;
	text->lvl.bar[1].rect.h = 10;
	text->lvl.bar[1].rect.w = 800;
	text->reload_empty.rect.x = P_POS_X - 10;
	text->reload_empty.rect.y = P_POS_Y - 3;
	text->reload_empty.rect.w = 50;
	text->reload_empty.rect.h = 5;
	text->reload_full.rect.x = P_POS_X - 10;
	text->reload_full.rect.y = P_POS_Y - 3;
	text->reload_full.rect.h = 5;
	while (i < 14)
	{
		text->lvl.lvlup_tex[i].rect.y = 200;
		text->lvl.lvlup_tex[i].rect.w = 200;
		text->lvl.lvlup_tex[i].rect.h = 360;
		text->lvl.amount[i] = 0;
		i++;
	}
}

// init the enemy struct
t_enemy	*enem_init()
{
	int		i = 0;
	t_enemy	*ret;
	ret = (t_enemy *)malloc(sizeof(t_enemy) * E_COUNT);
	bzero(ret, sizeof(t_enemy) * E_COUNT);
	while (i < E_COUNT)
	{
		ret[i].sign = 0;
		ret[i].type = 0;
		ret[i].frame.y = 0;
		i++;
	}
	return (ret);
}

// globals
void	init_global()
{
	egg_lvl_up_time = 0;
	real_speed = 4;
	speed = real_speed;
	player_hit = 0;
	run_anim = 0;
	dir = 0;
	enemy_timer = 0;
	up_down = 0;
	left_right = 0;
	screen.x = 0;
	screen.y = 0;
	screen.w = 1280;
	screen.h = 800;
	full_heart.x = 0;
	full_heart.y = 0;
	full_heart.w = 16;
	full_heart.h = 16;
	empty_heart.x = 16;
	empty_heart.y = 0;
	empty_heart.w = 16;
	empty_heart.h = 16;
	phbox.x = CENTER_X - 10;
	phbox.y = CENTER_Y - 10;
	phbox.w = 17;
	phbox.h = 20;
	big_phbox.x = CENTER_X - 100;
	big_phbox.y = CENTER_Y - 100;
	big_phbox.w = 200;
	big_phbox.h = 200;
	shot_happening = 0;
	normal_particle_blood_life = 20;

//spawn things
// {
		spawn_enemy_delayer = 95; //enemy spawn thing is here
		time_to_spike = 0;
		check_of_the_spawn = 0;
		current_boss_index = 0;
		current_spikespawn_index = 0;
		weak_spawn_checker = 0;
// }

	egg_dist_value = 5000;

	s_shake_active = 0;
	sh_x = 0;
	sh_y = 0;

	mag_full_empty.h = 16;
	mag_full_empty.w = 16;
	mag_full_empty.y = 0;
	mag_pos.w = 16;
	mag_pos.h = 16;

	particle_srect.w = 3;
	particle_srect.h = 3;
	particle_srect.y = 0;
	particle_dest.w = 6;
	particle_dest.h = 6;
	boss_particle_dest.w = 10;
	boss_particle_dest.h = 10;

	time_pos.h = 16;
	time_pos.w = 16;
	time_pos.y = 20;
	time_frame_pos.y = 0;
	time_frame_pos.w = 16;
	time_frame_pos.h = 16;

	dots_pos.x = 632;
	dots_pos.y = 20;
	dots_pos.h = 16;
	dots_pos.w = 16;

	orb_rect.w = 16;
	orb_rect.h = 16;
	orb_rect.y = 0;

	can_arrow = 0;

	rage_uprgade_active_frames = 0;
	hit_animation_active_frames = 0;

	lazy_minute_get_variable = 0;
	lazy_second_get_variable = 0;

	lvl_up_counter = 0;
	egg_amount_counter = 0;

	//global.h variables
	all_seconds = 0;

	reload_speed = 35;
	fire_rate = 7;
	stay_put = 0;
	pierce_amount = 1;
	max_shots = 5;
	bullet_speed = 12;
	max_bullet_life = 90;
	curr_sprite = 0;

	bullet_damage = 16;
	intsta_kill = 0;

	dmg_increase = 0;

	pl_hit_anim = 0;

	spike_spawn_active = 0;

	screen_shake_amount = 0;

	insta_kill_active = 0;

	more_shots_at_a_time = 0;

	split_shot_amount = 0;

	shock_active = 0;

	spawn_boss = 0;

	creep_active = 0;

	dead_whale_active = 0;

	dagger_active = 0;

	dark_aura_active = 0;

	rage_active = 0;
	rage_now = 0;
	rage_sprite = 0;

	shotti_sheet_fr.y = 0;
	shotti_sheet_fr.w = 32;
	shotti_sheet_fr.h = 32;

	fractal_rect.w = 10;
	fractal_rect.h = 10;

	instakill_rect.x = 192;
	instakill_rect.y = 0;
	instakill_rect.w = 32;
	instakill_rect.h = 32;

	enemies_killed_during_game = 0;
	bosses_killed_during_game = 0;
}

void	get_music_and_game_volume()
{
	int		fd;
	char	c;

	fd = open("game_audio/volume/music.txt", O_RDONLY);
	read(fd, &c, sizeof(char));
	global_music_volume = c - '0';
	close(fd);
	fd = open("game_audio/volume/game.txt", O_RDONLY);
	read(fd, &c, sizeof(char));
	global_game_volume = c - '0';
	close(fd);
	if (global_game_volume > 8 || global_game_volume < 0)
		global_game_volume = 0;
	if (global_music_volume > 8 || global_music_volume < 0)
		global_music_volume = 0;
}

//very messy function and a file only for initialising values and textures
void	init(t_wre *wre, t_player *player, t_textures *text, t_audio *audio)
{
	init_global();
	srand(time(0));
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(26);
	get_music_and_game_volume();
	manage_volume();
	SDL_CreateWindowAndRenderer(WIDTH, 720, 0, &wre->win, &wre->rend);
	player->anim.idle = get_texture(wre->rend, "sprites/player/pl.png");
	player->anim.r = get_texture(wre->rend, "sprites/player/run_file.png");
	player->anim.idle_dmg = get_texture(wre->rend, "sprites/player/pl-dmg.png");
	player->anim.r_dmg = get_texture(wre->rend, "sprites/player/run_file-dmg.png");
	player->anim.rage = get_texture(wre->rend, "sprites/player/pl-sheet.png");
	player->anim.rage_run = get_texture(wre->rend, "sprites/player/run_file-sheet.png");
	player->anim.rage_flame.text = get_texture(wre->rend, "sprites/flame/rage_flame.png");
	text->nums = get_texture(wre->rend, "sprites/tools/numbers.png");
	numbers_texture_sheet = get_texture(wre->rend, "sprites/tools/numbers.png");
	text->dots = get_texture(wre->rend, "sprites/tools/double_dot.png");
	double_dot_thexture_sprite = get_texture(wre->rend, "sprites/tools/double_dot.png");
	text->orb = get_texture(wre->rend, "sprites/orb_sheet.png");
	text->ground = get_texture(wre->rend, "sprites/use_this_fucking_file.png");
	text->cursor.text = get_texture(wre->rend, "sprites/tools/cursor.png");
	text->gun.text = get_texture(wre->rend, "sprites/real_gun.png");
	text->enemy.zomb.text = get_texture(wre->rend, "sprites/enemy/zombie_sheet.png");
	text->enemy.red_enemy.text = get_texture(wre->rend, "sprites/enemy/red_enem_test.png");
	text->enemy.red_enemy_hit = get_texture(wre->rend, "sprites/enemy/red_enem_test_dmg.png");
	text->enemy.annoying_enemy.text = get_texture(wre->rend, "sprites/enemy/annoying_enemy.png");
	text->enemy.annoying_hit = get_texture(wre->rend, "sprites/enemy/annoying_enemy_dmg.png");
	text->enemy.boss.text = get_texture(wre->rend, "sprites/enemy/boss_monster.png");
	text->enemy.boss_hit = get_texture(wre->rend, "sprites/enemy/boss_monster_dmg.png");
	text->enemy.pentagram.text = get_texture(wre->rend, "sprites/enemy/pentagram_sheet.png");
	text->enemy.brown_enem.text = get_texture(wre->rend, "sprites/enemy/brown_enem.png");
	text->enemy.brown_enem_hit = get_texture(wre->rend, "sprites/enemy/brown_enem_dmg.png");
	text->enemy.crab.text = get_texture(wre->rend, "sprites/enemy/new_crab.png");
	text->enemy.crab_hit = get_texture(wre->rend, "sprites/enemy/crab_hit.png");
	text->enemy.minotaur.text = get_texture(wre->rend, "sprites/enemy/minotaur.png");
	text->enemy.minotaur_hit = get_texture(wre->rend, "sprites/enemy/minotaur_hit.png");
	text->enemy.red_frog.text = get_texture(wre->rend, "sprites/enemy/red_frog.png");
	text->enemy.red_frog_hit = get_texture(wre->rend, "sprites/enemy/red_frog_hit.png");
	text->enemy.scorpion.text = get_texture(wre->rend, "sprites/enemy/scorpion.png");
	text->enemy.scorpion_hit = get_texture(wre->rend, "sprites/enemy/scorpion_hit.png");
	text->health = get_texture(wre->rend, "sprites/heart.png");
	shock.shock_tex = get_texture(wre->rend, "sprites/bullets/shock.png");
	text->lvl.bar[0].text = get_texture(wre->rend, "sprites/tools/xp_fill.png");
	text->lvl.bar[1].text = get_texture(wre->rend, "sprites/tools/xp_bar_empty.png");
	text->reload_empty.text = text->lvl.bar[1].text;
	text->reload_full.text = get_texture(wre->rend, "sprites/reload_bar.png");
	text->lvl.lvlup_tex[0].text = get_texture(wre->rend, "sprites/lvl/heart_lvl.png");
	text->lvl.lvlup_tex[1].text = get_texture(wre->rend, "sprites/lvl/gun_oil.png");
	text->lvl.lvlup_tex[2].text = get_texture(wre->rend, "sprites/lvl/field_maintenance-sheet.png");
	text->lvl.lvlup_tex[3].text = get_texture(wre->rend, "sprites/lvl/fractal.png");
	text->lvl.lvlup_tex[4].text = get_texture(wre->rend, "sprites/lvl/popcorn.png");
	text->lvl.lvlup_tex[5].text = get_texture(wre->rend, "sprites/lvl/insta-kill.png");
	text->lvl.lvlup_tex[6].text = get_texture(wre->rend, "sprites/lvl/sugar_rush.png");
	text->lvl.lvlup_tex[7].text = get_texture(wre->rend, "sprites/lvl/big_mag-2.png");
	text->lvl.lvlup_tex[8].text = get_texture(wre->rend, "sprites/lvl/electric.png");
	text->lvl.lvlup_tex[9].text = get_texture(wre->rend, "sprites/lvl/rage.png");
	text->lvl.lvlup_tex[10].text = get_texture(wre->rend, "sprites/lvl/toxic.png");
	text->lvl.lvlup_tex[11].text = get_texture(wre->rend, "sprites/lvl/dead_whale.png");
	text->lvl.lvlup_tex[12].text = get_texture(wre->rend, "sprites/lvl/dagger.png");
	text->lvl.lvlup_tex[13].text = get_texture(wre->rend, "sprites/lvl/skull_lvl-sheet.png");
	dmg_upgrade_tex = get_texture(wre->rend, "sprites/lvl/big_caliber.png");
	crit_upgrade_tex = get_texture(wre->rend, "sprites/lvl/insta-kill.png");
	text->enemy.zomb_hit_text = get_texture(wre->rend, "sprites/enemy/zombie_hit.png");
	text->enemy.zomb_hit_text = get_texture(wre->rend, "sprites/enemy/zombie_hit.png");
	text->enemy.flame.text = get_texture(wre->rend, "sprites/flame/penta_flame.png");
	text->bullet = get_texture(wre->rend, "sprites/bullets/shotti_sheet.png");
	text->blood = get_texture(wre->rend, "sprites/tools/blood_sheet.png");
	text->boss_bood = get_texture(wre->rend, "sprites/tools/boss_splatter.png");
	text->mag = get_texture(wre->rend, "sprites/bullets/mag-sheet.png");
	text->explosion = get_texture(wre->rend, "sprites/flame/dead_whale_exp.png");
	text->dagger = get_texture(wre->rend, "sprites/dagger/dagger_weapon_sheet.png");
	text->dagger_crit = get_texture(wre->rend, "sprites/dagger/crit_knife.png");
	text->dark_flame = get_texture(wre->rend, "sprites/flame/dark_flame.png");
	text->dark_aura = get_texture(wre->rend, "sprites/flame/dark_aura-sheet.png");
	text->off_color_status = get_texture(wre->rend, "sprites/tools/off_color.png");
	text->black_background = get_texture(wre->rend, "sprites/tools/black_background.png");
	text->white_particle = get_texture(wre->rend, "sprites/player/death_particle.png");
	text->button = get_texture(wre->rend, "sprites/tools/button.png");
	text->audio_bar = get_texture(wre->rend, "sprites/tools/volume_bar.png");
	text->audio_slider = get_texture(wre->rend, "sprites/tools/volume_slider.png");
	text->audio_bar_remain = get_texture(wre->rend, "sprites/tools/xp_bar_empty.png");
	text->confetti = get_texture(wre->rend, "sprites/tools/confetti.png");
	egg_full_texture = get_texture(wre->rend, "sprites/egg_arrow/egg.png");
	egg_hit_full_texture = get_texture(wre->rend, "sprites/egg_arrow/egg_hit.png");
	white_orb = get_texture(wre->rend, "sprites/egg_arrow/white_orb.png");
	eggshell_tex = get_texture(wre->rend, "sprites/egg_arrow/egg_shatter.png");
	arrow_pointer = get_texture(wre->rend, "sprites/egg_arrow/pointer.png");
	creep_upgrade_texture = get_texture(wre->rend, "sprites/player/real_slime.png");
	alphabet_full_texture = get_texture(wre->rend, "sprites/tools/alphabet.png");
	audio->gun_shoot = Mix_LoadWAV("game_audio/gun/402008__eardeer__gunshot-high-3.wav");
	audio->hurt[0] = Mix_LoadWAV("game_audio/effect/515623__mrickey13__playerhurt1.wav");
	audio->hurt[1] = Mix_LoadWAV("game_audio/effect/515624__mrickey13__playerhurt2.wav");
	audio->walk[0] = Mix_LoadWAV("game_audio/effect/390757__d00121058__fx-004-footstep-gravel-r.wav");
	audio->walk[1] = Mix_LoadWAV("game_audio/effect/390758__d00121058__fx-003-footstep-gravel-l.wav");
	audio->coin[0] = Mix_LoadWAV("game_audio/coin/173323__soundnimja__coin-4.wav");
	audio->coin[1] = Mix_LoadWAV("game_audio/coin/173324__soundnimja__coin-3.wav");
	audio->enem_death[0] = Mix_LoadWAV("game_audio/enem_hit/zombie_ded.wav");
	audio->enem_death[1] = Mix_LoadWAV("game_audio/enem_hit/488294__combine2005__explosionretro.wav");
	audio->hit = Mix_LoadWAV("game_audio/enem_hit/Hitmarker sound.wav");
	audio->acid = Mix_LoadWAV("game_audio/enem_hit/acid.wav");
	audio->dead_whale = Mix_LoadWAV("game_audio/effect/dead_whale_exp.wav");
	audio->dagger_woosh = Mix_LoadWAV("game_audio/dagger/knife_deploy.wav");
	audio->dark_aura = Mix_LoadWAV("game_audio/lvl/dark_aura_sound.wav");
	audio->player_death[0] = Mix_LoadWAV("game_audio/game_over/death_first.wav");
	audio->player_death[1] = Mix_LoadWAV("game_audio/game_over/death_second.wav");
	audio->player_death[2] = Mix_LoadWAV("game_audio/game_over/death_last.wav");
	audio->button = Mix_LoadWAV("game_audio/effect/button-16.wav");
	audio->rollover = Mix_LoadWAV("game_audio/effect/hover.wav");
	audio->menu_music = Mix_LoadWAV("game_audio/music/menu.wav");
	audio->escape_victory = Mix_LoadWAV("game_audio/music/POL-crazy-escape-stinger.wav");
	card_choosing_soundeffect = Mix_LoadWAV("game_audio/lvl/244355__soneproject__snr002.wav");
	lvl_up_instance_soundeffect = Mix_LoadWAV("game_audio/lvl/126422__makofox__level-up.wav");
	audio->gun_reload = Mix_LoadWAV("game_audio/gun/reload_gun.wav");
	shock.shock_audio = Mix_LoadWAV("game_audio/gun/spark.wav");
	text->enemy.clang = Mix_LoadWAV("game_audio/effect/clang.wav");
	rage_scream = Mix_LoadWAV("game_audio/effect/rage_scream.wav");
	flame_burst = Mix_LoadWAV("game_audio/effect/flame_burst.wav");
	egg_crack = Mix_LoadWAV("game_audio/effect/egg_crack.wav");
	hit_soundeffect = Mix_LoadWAV("game_audio/enem_hit/Hitmarker sound.wav");
	coin_soundeffect = Mix_LoadWAV("game_audio/coin/173324__soundnimja__coin-3.wav");
	critical_hit_soundeffect = Mix_LoadWAV("game_audio/effect/ror2crit3.wav");
	music_audio_file = Mix_LoadWAV("game_audio/music/POL-crazy-escape-long.wav");
	rects(text);
	player->anim.rect.x = P_POS_X;
	player->anim.rect.y = P_POS_Y;
	player->anim.rect.w = 64;
	player->anim.rect.h = 64;
	player->anim.rage_flame.rect.x = P_POS_X - 15;
	player->anim.rage_flame.rect.y = P_POS_Y - 66;
	player->anim.rage_flame.rect.w = 64;
	player->anim.rage_flame.rect.h = 96;
	run_init(player);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawBlendMode(wre->rend, SDL_BLENDMODE_BLEND);
	SDL_SetWindowFullscreen(wre->win, SDL_WINDOW_FULLSCREEN);
}
