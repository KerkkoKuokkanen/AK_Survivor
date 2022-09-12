
#include "../top_down.h"

void	rage_flame(t_tr *flame, t_graphics *all, int sign)
{
	SDL_Rect	frame = {0, 0, 32, 48};
	static int	now = 0;
	static int	time = 0;
	int			fr = 0;

	if (sign == (-1))
	{
		now = 1;
		time = 0;
		return ;
	}
	if (now == 1)
	{
		fr = 32 * (time / 6);
		frame.x = fr;
		screen_shaker(&flame->rect.x, &flame->rect.y);
		ysort(NULL, flame->text, &flame->rect, &frame, NULL, 0, 0, 0);
//		make_curr_graph(all, flame->text, &flame->rect, &frame, NULL, 0, 0);
		time++;
		if (time >= 30)
			now = 0;
	}
}

int	get_the_right_player_sprite()
{
	if (rage_sprite == 1)
	{
		rage_sprite = 0;
		rage_uprgade_active_frames = 600;
	}
	if (rage_uprgade_active_frames > 0)
	{
		rage_uprgade_active_frames--;
		if (rage_uprgade_active_frames < 90)
		{
			if (((rage_uprgade_active_frames / 10) % 2) == 0)
				return (2);
			return (0);
		}
		return (2);
	}
	if (pl_hit_anim == 1)
	{
		pl_hit_anim = 0;
		hit_animation_active_frames = 90;
	}
	if (hit_animation_active_frames > 0)
	{
		hit_animation_active_frames--;
		if (((hit_animation_active_frames / 10) % 2) == 0)
			return (1);
		return (0);
	}
	return (0);
}

void	p_anim(t_player player, t_graphics *all, uint8_t bool)
{
	int			right_sprite = get_the_right_player_sprite();
	int			i = run_anim / 5;
	t_tex		pl_tex;

	rage_flame(&player.anim.rage_flame, all, 0);
	screen_shaker(&player.anim.rect.x, &player.anim.rect.y);
	run_anim++;
	if (run_anim == 30)
		run_anim = 0;
	if (bool == 0)
	{
		if (right_sprite == 1)
			pl_tex = player.anim.idle_dmg;
		else if (right_sprite == 2)
			pl_tex = player.anim.rage;
		else
			pl_tex = player.anim.idle;
		if (dir == 1)
		{
			player.anim.rect.x -= 32;
			ysort(NULL, pl_tex, &player.anim.rect, NULL, NULL, 0, 1, 1);
		}
		else
			ysort(NULL, pl_tex, &player.anim.rect, NULL, NULL, 0, 0, 1);
		return ;
	}
	if (right_sprite == 1)
		pl_tex = player.anim.r_dmg;
	else if (right_sprite == 2)
		pl_tex = player.anim.rage_run;
	else
		pl_tex = player.anim.r;
	if (dir == 0)
		ysort(NULL, pl_tex, &player.anim.rect, &player.anim.run[i], NULL, 0, 0, 1);
	else
	{
		player.anim.rect.x -= 32;
		ysort(NULL, pl_tex, &player.anim.rect, &player.anim.run[i], NULL, 0, 1, 1);
	}
}

void	ground_scroll(uint8_t lr, uint8_t ud, SDL_Rect *g_move)
{
	if (lr == 1)
		g_move->x += speed / 2;
	if (lr == 2)
		g_move->x -= speed / 2;
	if (ud == 1)
		g_move->y -= speed / 2;
	if (ud == 2)
		g_move->y += speed / 2;
	if (g_move->x < 0)
		g_move->x += GW;
	if (g_move->x > GW)
		g_move->x -= GW;
	if (g_move->y < 0)
		g_move->y += GH;
	if (g_move->y > GH)
		g_move->y -= GH;
}
