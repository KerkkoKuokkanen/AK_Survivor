
#include "../top_down.h"
#define	DARK_LIFE 1200
#define	DARK_HBOX_X 330
#define DARK_HBOX_Y 210
#define D_START_X 455
#define D_START_Y 270
#define H_START_X 475
#define H_START_Y 340
#define DEST_WH 360
#define DMG_TICK 8

void	dark_aura_start(t_textures *text, t_audio *audio, int life)
{
	SDL_Rect	dest = {605 - 32, 314 - 80, 64 + 64, 96 + 96};
	SDL_Rect	frame = {0, 0, 32, 48};
	static int	now = 0;
	static int	time = 0;
	int			fr = 0;

	if (life == DARK_LIFE)
	{
		Mix_PlayChannel(18, audio->dark_aura, 0);
		now = 1;
		time = 0;
	}
	if (now == 1)
	{
		fr = 32 * (time / 6);
		frame.x = fr;
		screen_shaker(&dest.x, &dest.y);
		ysort(NULL, text->dark_flame, &dest, &frame, NULL, 0, 0, 0);
		time++;
		if (time >= 30)
			now = 0;
	}
}

int	get_the_aura_damage(Mix_Chunk *crit)
{
	if (insta_kill_active == 0)
		return (bullet_damage + bullet_damage + bullet_damage);
	int	random;
	int	correct = 1;
	int	range = 17;

	range -= insta_kill_active;
	random = rand() % range;
	if (random == correct)
	{
		Mix_PlayChannel(17, crit, 0);
		return ((bullet_damage + bullet_damage + bullet_damage) * 2);
	}
	return (bullet_damage + bullet_damage + bullet_damage);
}

void	enem_hit_by_aura(t_enemy *enem, t_audio *audio)
{
	int				i = 0;
	const SDL_Rect	hbox = {H_START_X, H_START_Y, DARK_HBOX_X, DARK_HBOX_Y};
	static int		tick = 0;

	while (i < E_COUNT)
	{
		if (enem[i].type != 0)
		{
			if (tick == DMG_TICK && place_meeting(hbox, enem[i].hbox))
			{
				enem[i].got_hit = ENEM_GOT_HIT;
				enem[i].hp -= get_the_aura_damage(critical_hit_soundeffect);
				Mix_PlayChannel(4, audio->hit, 0);
				if (enem[i].hp <= 0)
				{
					enem_kill_counter(&enem[i]);
					orb_main(enem, NULL, NULL, NULL, i);
					particle_main(&enem[i], NULL, NULL, i);
					enem[i].type = 0;
					Mix_PlayChannel(2, audio->enem_death[0], 0);
						dead_whale_explosion_main(enem, i, NULL, 0, NULL, NULL);
					dagger_main(enem, i, NULL, NULL, NULL);
					if (s_shake_active != 2)
						s_shake_active = 1;
					screen_shake_amount = 1;
				}
			}
		}
		i++;
	}
	if (tick == DMG_TICK)
		tick = 0;
	tick++;
}

void	manage_aura(t_enemy *enem, t_textures *text, t_audio *audio, t_graphics *all, int life)
{
	SDL_Rect		dest = {D_START_X, D_START_Y, DEST_WH, DEST_WH};

	dark_aura_start(text, audio, life);
	enem_hit_by_aura(enem, audio);
	screen_shaker(&dest.x, &dest.y);
	if (life < 90)
	{
		if (((life / 10) % 2) == 0)
			make_curr_graph(all, text->dark_aura, &dest, NULL, NULL, 0, 0);
	}
	else
		make_curr_graph(all, text->dark_aura, &dest, NULL, NULL, 0, 0);
}

void	dark_aura_main(t_enemy *enem, t_textures *text, t_audio *audio, t_graphics *all)
{
	static int	life = 0;

	if (enem == NULL && text == NULL && audio == NULL && all == NULL)
	{
		life = 0;
		return ;
	}
	if (dark_aura_active == 0 && life <= 0)
		return ;
	if (dark_aura_active == 1)
	{
		life = DARK_LIFE;
		Mix_PlayChannel(19, flame_burst, 0);
		dark_aura_active = 0;
	}
	manage_aura(enem, text, audio, all, life);
	life -= 1;
}
