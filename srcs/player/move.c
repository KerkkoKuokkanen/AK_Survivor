
#include "../top_down.h"

void	play_audio(uint8_t bool, Mix_Chunk **walk)
{
	static int	timer = 0;
	static int	lr = 0;

	if (bool != 0 && timer == 0)
	{
		timer = 19;
		Mix_PlayChannel(7, walk[lr], 0);
		if (lr == 1)
			lr = 0;
		else
			lr = 1;
	}
	if (timer > 0)
		timer--;
}

void	move_player(t_player *player, t_keys keys, t_graphics *all, SDL_Rect *g_move, int x, Mix_Chunk **walk)
{
	uint8_t	bool = 0;

	left_right = 0;
	up_down = 0;
	if (keys.right == 1)
	{
		bool = 1;
		left_right = 1;
	}
	else if (keys.left)
	{
		bool = 2;
		left_right = 2;
	}
	if (keys.up == 1)
	{
		up_down = 1;
		bool = 3;
	}
	else if (keys.down == 1)
	{
		up_down = 2;
		bool = 4;
	}
	play_audio(bool, walk);
	if (x < player->anim.rect.x + 16)
		dir = 1;
	else if (x > player->anim.rect.x + 16)
		dir = 0;
	p_anim(*player, all, bool);
	ground_scroll(left_right, up_down, g_move);
}
