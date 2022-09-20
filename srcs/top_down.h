#ifndef TOP_DOWN_H

# define TOP_DOWN_H

# define WIDTH 1280
# define HEIGHT 800
# define START_INIT -6
# define FRAME 17
# define GW 640
# define GH 400
# define CENTER_X 636
# define CENTER_Y 428
# define P_POS_X 620
# define P_POS_Y 380
# define PI 3.14159265
# define RAD 0.0174532
# define BLOOD_LIFE 20
# define PARTICLE_AMOUNT 50
# define E_COUNT 800 //800 is a good amount
# define BULLET_COUNT 1800
# define DEATH_OF_PLAYER 1

# define SPIKE_DELAY 30
# define NUM_JUMP 16

# define E_MAP_Y 16
# define E_MAP_X 32

# define X_LEFT -600
# define X_RIGHT 600
# define Y_UP -600
# define Y_DOWN 600

# define Y_MAX 1000
# define Y_MIN -200

# define X_MAX 1480
# define X_MIN -200

# define INDEX_STOP 12345678

# define ORB_AMOUNT 500

# define ENEM_GOT_HIT 5

# define SPRITE_AMOUNT 19000

# define SHOCK_RANGE 100
# define SHOCK_TIME 6

# define INSTAKILL_DMG 500

# define COORD_ARRAY_SIZE 2000

# include <stdio.h>
# include <SDL2/SDL.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_mixer/SDL_mixer.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include "global.h"
# include <strings.h>

int			player_hit;

int			speed;
int			real_speed;

int			s_shake_active;
int			sh_x;
int			sh_y;

int			can_arrow;

int			normal_particle_blood_life;

int			lvl_up_counter;

int			egg_amount_counter;

// enemy spawning stuff:
// {
		int	spawn_enemy_delayer;
		int	time_to_spike;
		int	check_of_the_spawn;
		int	current_boss_index;
		int	current_spikespawn_index;
		int	weak_spawn_checker;
// }

int			shot_happening;
int			left_right;
int			up_down;
int			run_anim;
int			angle;
int			enemy_timer;
uint8_t		direction_of_the_gun;
SDL_Rect	screen;
SDL_Rect	big_screen;

SDL_Rect	full_heart;
SDL_Rect	empty_heart;

int			egg_lvl_up_time;

SDL_Rect	phbox;
SDL_Rect	big_phbox;

//particle rects so we dont have to initialize them all the time
SDL_Rect	particle_dest;
SDL_Rect	boss_particle_dest;
SDL_Rect	particle_srect;

//Rects for mag so we dont need to initialize it every time
SDL_Rect	mag_full_empty;
SDL_Rect	mag_pos;

SDL_Rect	time_pos;
SDL_Rect	time_frame_pos;
SDL_Rect	dots_pos;

SDL_Rect	shotti_sheet_fr;
SDL_Rect	fractal_rect;

SDL_Rect	orb_rect;

SDL_Rect	pentagram_frame;

SDL_Rect	instakill_rect; //rect for the instakill shot

int			all_seconds;

int			spike_spawn_active;

int			spawn_boss;

int			egg_dist_value;

int			aspect_ratio;
int			window_check_value;

int			lazy_minute_get_variable;
int			lazy_second_get_variable;

int			global_music_volume;
int			global_game_volume;

int			hit_animation_active_frames;
int			rage_uprgade_active_frames;

Mix_Chunk	*rage_scream;
Mix_Chunk	*flame_burst;
Mix_Chunk	*egg_crack;
Mix_Chunk	*hit_soundeffect;
Mix_Chunk	*coin_soundeffect;
Mix_Chunk	*card_choosing_soundeffect;
Mix_Chunk	*lvl_up_instance_soundeffect;
Mix_Chunk	*critical_hit_soundeffect;
Mix_Chunk	*music_audio_file;

typedef struct	t_tex
{
	SDL_Texture	*text;
}				t_tex;

t_tex		egg_full_texture;
t_tex		egg_hit_full_texture;
t_tex		eggshell_tex;
t_tex		white_orb;
t_tex		arrow_pointer;
t_tex		dmg_upgrade_tex;
t_tex		crit_upgrade_tex;
t_tex		creep_upgrade_texture;
t_tex		alphabet_full_texture;
t_tex		numbers_texture_sheet;
t_tex		double_dot_thexture_sprite;

typedef struct	t_tr
{
	t_tex		text;
	SDL_Rect	rect;
}				t_tr;

typedef struct	t_itr
{
	t_tr	tr;
	int		index;
}				t_itr;

typedef struct	t_wre
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Event		event;
}				t_wre;

typedef struct t_anim
{
	t_tex		idle;
	t_tex		r;
	t_tex		idle_dmg;
	t_tex		r_dmg;
	t_tex		rage;
	t_tex		rage_run;
	t_tr		rage_flame;
	SDL_Rect	rect;
	SDL_Rect	run[6];
}				t_anim;

typedef struct	t_player
{
	t_anim	anim;
}				t_player;

typedef struct	t_keys
{
	uint8_t	left;
	uint8_t	right;
	uint8_t	down;
	uint8_t	up;
	uint8_t	click;
	uint8_t	r_key;
	uint8_t	tab;
	uint8_t	escape;
}				t_keys;

typedef struct	t_index
{
	int	y;
	int	enem;
}				t_index;

typedef struct	t_text_enemy
{
	t_tr		zomb;
	t_tex		zomb_hit_text;
	t_tr		red_enemy;
	t_tex		red_enemy_hit;
	t_tr		boss;
	t_tex		boss_hit;
	t_tr		annoying_enemy;
	t_tex		annoying_hit;
	t_tr		pentagram;
	t_tr		brown_enem;
	t_tr		flame;
	t_tex		brown_enem_hit;
	t_tr		crab;
	t_tex		crab_hit;
	t_tr		minotaur;
	t_tex		minotaur_hit;
	t_tr		red_frog;
	t_tex		red_frog_hit;
	t_tr		scorpion;
	t_tex		scorpion_hit;
	Mix_Chunk	*clang;
}				t_text_enemy;

typedef struct	t_shot_coord
{
	int	x;
	int	y;
	int	x2;
	int	y2;
}				t_shot_coord;

typedef struct	t_lvl_audio
{
	Mix_Chunk	*card;
	Mix_Chunk	*lvl;
}				t_lvl_audio;


typedef struct	t_audio
{
	Mix_Chunk	*gun_shoot;
	Mix_Chunk	*gun_reload;
	Mix_Chunk	*hurt[2];
	Mix_Chunk	*walk[2];
	Mix_Chunk	*coin[2];
	Mix_Chunk	*enem_death[2];
	Mix_Chunk	*hit;
	Mix_Chunk	*acid;
	Mix_Chunk	*dead_whale;
	Mix_Chunk	*dagger_woosh;
	Mix_Chunk	*dark_aura;
	Mix_Chunk	*player_death[3];
	Mix_Chunk	*button;
	Mix_Chunk	*rollover;
	Mix_Chunk	*menu_music;
	Mix_Chunk	*escape_victory;
	t_lvl_audio	lvl;
}				t_audio;

typedef struct	t_level_up
{
	t_tr	bar[2];
	t_tr	lvlup_tex[14];
	int		amount[14];
}				t_level_up;

typedef struct	t_shock
{
	Mix_Chunk		*shock_audio;
	t_tex			shock_tex;
}				t_shock;

t_shock			shock;

typedef struct	s_ysort
{
	int		index;
	double	y;
	int		sign;	//sign tells us where the current texture is or (-1) for end
}				t_ysort;

typedef struct	t_textures
{
	t_tex			ground;
	t_tex			orb;
	t_tex			blood;
	t_tex			boss_bood;
	SDL_Rect		g_move;
	t_tr			cursor;
	t_tr			gun;
	t_tr			shot;
	t_tex			health;
	t_tex			bullet;
	SDL_Rect		s_sheet;
	t_text_enemy	enemy;
	t_level_up		lvl;
	t_tr			reload_empty;
	t_tr			reload_full;
	t_tex			mag;
	t_tex			nums;
	t_tex			dots;
	t_tex			explosion;
	t_tex			dagger;
	t_tex			dagger_crit;
	t_tex			dark_flame;
	t_tex			dark_aura;
	t_tex			off_color_status;
	t_tex			black_background;
	t_tex			white_particle;
	t_tex			button;
	t_tex			audio_slider;
	t_tex			audio_bar;
	t_tex			audio_bar_remain;
	t_tex			confetti;
}				t_textures;

// quarter is either 1, 2, 3 or 4 each representing a segment of the screen

typedef struct	t_map
{
	int	*index;
	int	occupied;
	int	quarter;
}				t_map;

typedef struct	t_vec
{
	double	x;
	double	y;
}				t_vec;

typedef struct	t_shot
{
	int			delay;
	int			reload;
	int			shot_count;
	int			time_to_shoot;
}				t_shot;

typedef struct	t_orb
{
	int			hit;
	int			amount;
	int			on_screen;
	int			sprite_index;
	SDL_Rect	pos;
	t_vec		dir;
}				t_orb;

typedef struct	t_push_back
{
	t_vec	dir;
	int		duration;
}				t_push_back;

typedef struct	t_particle
{
	t_vec		dir;
	t_vec		pos;
	SDL_Rect	dest;
}				t_particle;

typedef struct	s_egg
{
	t_vec		dest;
	SDL_Rect	frame;
	SDL_Rect	hbox;
	int			hits;
	int			got_hit;
}				t_egg;

typedef struct	t_blood_spatter
{
	uint8_t		tru;
	int			life_time;
	t_vec		starting_pos;
	t_particle	blood[PARTICLE_AMOUNT];
}				t_blood_spatter;

typedef struct	t_bullets
{
	uint8_t		tru;
	int			life_time;
	int			type;
	t_vec		pos;
	t_vec		dir;
	SDL_Rect	hbox;
}				t_bullets;

typedef struct	t_graphics
{
	t_tex		tex;
	SDL_Rect	dest;
	SDL_Rect	frame;
	SDL_Point	point;
	int			sign;
	int			angle;
	int			nulls;	//nulls corresponds to the ones that were not given
}				t_graphics;

typedef struct	t_shock_anim
{
	int	in_use;
	int	source;
	int	victim;
	int	time;
}				t_shock_anim;

typedef struct	t_all
{
	t_graphics	graphics[SPRITE_AMOUNT];
	int			curr;
}				t_all;

// type is just a number for each enemy. if it is 0 then there is no enemy
// quarter tells us where aproximately the enemy is, so we can make our shooting more
// performance friendly

typedef struct	t_enemy
{
	int			type;
	int			hp;
	int			got_shot;
	t_push_back	push;
	int			sign;
	t_tr		text;
	t_tex		hit_text;
	t_vec		pos;
	t_vec		dir;
	SDL_Rect	frame;
	int			got_hit;
	int			frc;
	int			push_back_amount;
	double		enem_speed;
	SDL_Rect	hbox;
	int			on_screen;
	int			life_time;
}				t_enemy;

int			weak_enem_spawn(t_enemy *enem, t_text_enemy text, int current);
void		enem_kill_counter(t_enemy *enem);
void		manage_volume();
int			audio_menu(t_graphics *all, int x, int y, uint8_t click, t_textures *text, t_audio *audio);
int			rend_audio_menu(SDL_Renderer *rend, int x, int y, uint8_t click, t_textures *text, t_audio *audio);

void		main_menu(t_wre *wre, t_graphics *all, t_textures *text, t_audio *audio, t_keys *keys);
void		show_player_status(t_graphics *all, SDL_Renderer *rend, t_keys *keys, t_textures *text, t_tr *cursor);

void		put_text_to_screen(t_graphics *all, int x_start, int y_start, char *text, unsigned const int text_size, const int font);
void		rend_put_text_to_screen(SDL_Renderer *rend, int x_start, int y_start, char *text, unsigned const int text_size, const int font);

void		dark_aura_main(t_enemy *enem, t_textures *text, t_audio *audio, t_graphics *all);
int			pause_menu(t_graphics *all, t_wre *wre, t_textures *text, t_audio *audio, t_keys *keys);

void		bigger_smaller_indicator(SDL_Rect *one, SDL_Rect *two, int x, int y, int sign);

void		dagger_main(t_enemy *enem, int sign, t_graphics *all, t_textures *text, t_audio *audio);

void		move_enemy_from_player(t_vec *dest);

void		dead_whale_explosion_main(t_enemy *enem, int curr, t_graphics *all, int sign, t_audio *audio, t_tex *explosion);

void		creep_main(t_enemy *enem, t_graphics *all, t_audio *audio);

t_vec		*egg_main(t_bullets *bullets, t_graphics *all, int sign);
void		egg_level_screen(SDL_Renderer *rend, t_tr cursor, t_keys *keys, t_graphics *all);
void		arrow_to_egg(t_graphics *all);

void		make_nulls(int *nulls, int i);
void		ysort(t_graphics *all, t_tex text, SDL_Rect *dest, SDL_Rect *frame, SDL_Point *point, int angle, int sign, int call_from);

void		make_curr_graph(t_graphics *all, t_tex text, SDL_Rect *dest, SDL_Rect *frame, SDL_Point *point, int angle, int sign);
void		put_images_to_screen(SDL_Renderer *rend, t_graphics *all);

void		fractal_shot_creator(t_bullets *bullets, int index);

void		choose_one_two_three(t_itr *one, t_itr *two, t_itr *three, t_level_up *lvl, int *exhaust);

void		make_the_extra_popcorn_shots(t_bullets *bullets, int index);

void		choose_enemy(t_enemy *enem, t_text_enemy text, int sign);

void		choose_enem_anim_function(t_enemy *enem, t_graphics *all, t_tex text);

void		ysort_main(t_graphics *all, t_tex text, SDL_Rect *dest, SDL_Rect *frame,
							SDL_Point *point, int angle, int sign, int call_from);

void		spike_spawn(t_enemy *enemy, int amount, t_text_enemy text);
int			spike_amount_table();

void		rage_flame(t_tr *flame, t_graphics *all, int sign);

int			cmp_func(const void *a, const void *b);

int			victory_screen(t_graphics *all, t_wre *wre, t_audio *audio, t_textures *text, t_player *player, t_keys *keys, t_enemy *enem);

void		shock_the_enemies(t_enemy *enem, t_graphics *all, Mix_Chunk *death, int curr, int sign);

void		boss_spawner(t_enemy *enem, t_text_enemy *text, t_graphics *all, int sign, int boss_lifetime);
void		boss_particle(t_enemy *enem, t_tex *blood, t_graphics *all, int sign);

void		put_number_to_screen(t_graphics *all, int number, int x, int y, int size);
void		rend_put_number_to_screen(SDL_Renderer *rend, int number, int x, int y, int size);
void		move_dest_from_player(t_vec *dest);
t_keys		init_keys();
int			get_the_bullet_type();
t_enemy		*enem_init();
float		float_rand();
double		calc_a(t_vec v1, t_vec v2);
int			degree(double angle);
void		move_pos(t_vec *pos);
void		manage_screen_shake();
void		screen_shaker(int *x, int *y);
int			possible_move(SDL_Rect enem, SDL_Rect hbox, t_vec dir);
int			check_the_space_to_spawn(t_enemy *enem, int i);
void		push_back_main(t_enemy *enem, int curr);
void		draw_bar(t_graphics *all, t_tr full, t_tr empty);
void		cursor_to_screen(t_graphics *all, t_tr cursor, int x, int y);
void		enemy_main(t_enemy *enem, t_text_enemy text, t_graphics *all);
int			place_meeting(SDL_Rect box, SDL_Rect hit);
int			point_on_map(double x, double y);
int			point_meeting(int x, int y, SDL_Rect box);
int			get_the_num_from_time(int time, int sign);
t_map		**enem_map();
void		full_screen(t_graphics *all, t_wre *wre, t_textures *text, t_audio *audio, int x, int y, uint8_t *click);
void		audio_menu_screen_aspect_ratio(t_graphics *all, t_textures *text, t_audio *audio, int x, int y, uint8_t click, int *hover);
SDL_Rect	scale_the_rect(SDL_Rect dest);
void		update_enem_hbox(t_enemy *enem);
SDL_Rect	create_move_hbox(t_enemy *enem, t_vec fpos);
void		move_main(t_enemy *enem, int i, t_text_enemy text);
void		respawn_same_enemy(t_enemy *enem, int i, t_text_enemy text);
void		make_coord_for_enemy(t_enemy *enem);
void		choose_enem_anim(t_enemy *enem, t_graphics *all);
void		updates(t_graphics *all, t_tex ground, SDL_Rect g_move);
void		sort_enemy_array(t_enemy *enem, t_graphics *all);
void		p_anim(t_player player, t_graphics *all, uint8_t bool);
void		ft_keys(SDL_Event event, t_keys *keys);
void		run_init(t_player *player);
void		upgrade_chosen_attribute(uint8_t bool, int *exhaust, int *amount);
void		bigger_smaller_rect(SDL_Rect *one, SDL_Rect *two, SDL_Rect *three, int x, int y, int sign);
void		init(t_wre *wre, t_player *player, t_textures *text, t_audio *audio);
void		gun(t_tr gun, int x, int y, SDL_Rect player, t_graphics *all);
void		ground_scroll(uint8_t lr, uint8_t ud, SDL_Rect *g_move);
int			figure_the_delay(clock_t start, clock_t end);
void		move_player(t_player *player, t_keys keys, t_graphics *all, SDL_Rect *g_move, int x, Mix_Chunk **walk);
void		shoot(uint8_t *click);
void		orb_main(t_enemy *enem, t_graphics *all, t_tex *orb, Mix_Chunk **coin, int sign);
void		p_hit(double len, SDL_Rect hbox, int type, t_enemy *enem);
void		lvl_c_to_screen(SDL_Renderer *rend, t_tr cursor, int x, int y);
void		make_boss(t_enemy *enem, t_text_enemy text, int hp, int lifetime);
void		level_up_main(t_level_up *lvl, int amount, SDL_Renderer *rend,
						t_tr *cursor, t_keys *keys, t_lvl_audio *lvl_up, t_graphics *all, int sign);
int			health_main(t_tex *heart, t_graphics *all, Mix_Chunk **hurt, int sign);
t_tex		get_texture(SDL_Renderer *rend, char *filepath);
int			get_frame_multi(int frame_multi);
void		time_main(int time, t_graphics *all, t_tex *nums, t_tex *dots, int sign);
SDL_Texture	*get_ground(SDL_Renderer *rend);
void		init_global();
void		pre_game();
void		reset_keys(t_keys *keys);
void		clear_screen(t_graphics *all, size_t size);
void		mag_main(int shot_count, t_tex mag, t_graphics *all);
void		particle_main(t_enemy *enem, t_tex *blood, t_graphics *all, int sign);
void		bullets_main(int x, int y, uint8_t *key, t_graphics *all, t_tex *bullet, t_enemy *enem,
							Mix_Chunk *gun_shoot, Mix_Chunk *hitmark, Mix_Chunk **enem_death, t_tex *mag, uint8_t *r_key,
							t_tr *reload_full, t_tr *reload_empty, Mix_Chunk *reload);
int			game_over(t_graphics *all, t_textures *text, t_player *player, t_wre *wre, t_audio *audio, t_keys *keys);

#endif