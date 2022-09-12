
#include "../top_down.h"

void	anim_zomb(t_enemy *enem, t_graphics *all, t_tex text)
{
	if (stay_put == 0)
	{
		enem->frc++;
		if (enem->frc == 20)
			enem->frc = 0;
	}
	if (place_meeting(screen, enem->text.rect) == 0)
		return ;
	enem->on_screen = 1;
	int	x = enem->text.rect.x - 32;
	int	s = enem->text.rect.x;
	if (enem->frc < 10)
		enem->frame.x = 0;
	else
		enem->frame.x = 64;
	if (enem->text.rect.x > P_POS_X)
		enem->sign = 0;
	else
	{
		enem->text.rect.x = x;
		enem->sign = SDL_FLIP_HORIZONTAL;
	}
	ysort(NULL, text, &enem->text.rect, &enem->frame, NULL, 0, enem->sign, 0);
	enem->text.rect.x = s;
}

void	anim_red_enemy(t_enemy *enem, t_graphics *all, t_tex text)
{
	int	frame = enem->frc / 10;

	if (stay_put == 0)
	{
		enem->frc++;
		if (enem->frc == 60)
			enem->frc = 0;
	}
	if (place_meeting(screen, enem->text.rect) == 0)
		return ;
	enem->on_screen = 1;
	int	x = enem->text.rect.x - 32;
	int	s = enem->text.rect.x;
	enem->frame.x = 32 * frame;
	if (enem->text.rect.x > P_POS_X)
		enem->sign = 0;
	else
	{
		enem->text.rect.x = x;
		enem->sign = SDL_FLIP_HORIZONTAL;
	}
	ysort(NULL, text, &enem->text.rect, &enem->frame, NULL, 0, enem->sign, 0);
	enem->text.rect.x = s;
}

void	anim_annoying(t_enemy *enem, t_graphics *all, t_tex text)
{
	int	frame = enem->frc / 7;

	enem->enem_speed = 1;
	if (stay_put == 0)
	{
		enem->frc++;
		if (enem->frc == 56)
			enem->frc = 0;
	}
	if (place_meeting(screen, enem->text.rect) == 0)
		return ;
	enem->on_screen = 1;
	enem->frame.x = 16 * frame;
	if (enem->text.rect.x < P_POS_X)
		enem->sign = 0;
	else
		enem->sign = SDL_FLIP_HORIZONTAL;
	ysort(NULL, text, &enem->text.rect, &enem->frame, NULL, 0, enem->sign, 0);
}

int		get_boss_frame(t_enemy *enem)
{
	int	frame;

	if (enem->enem_speed == 2)
	{
		if (stay_put == 0)
		{
			enem->frc++;
			if (enem->frc >= 80)
				enem->frc = 0;
		}
		frame = enem->frc / 8;
		return (frame);
	}
	if (enem->enem_speed == 1)
	{
		if (stay_put == 0)
		{
			enem->frc++;
			if (enem->frc >= 50)
				enem->frc = 0;
		}
		frame = enem->frc / 5;
		return (frame);
	}
	frame = enem->frc / 10;
	if (stay_put == 0)
	{
		enem->frc++;
		if (enem->frc >= 100)
			enem->frc = 0;
	}
	return (frame);
}

void	anim_boss(t_enemy *enem, t_graphics *all, t_tex text)
{
	enem->life_time += 1;
	if (enem->life_time >= 2000)
		enem->enem_speed = 1;
	else if (enem->life_time >= 1000)
		enem->enem_speed = 2;
	if (place_meeting(screen, enem->text.rect) == 0)
		return ;
	enem->on_screen = 1;
	enem->frame.x = 192 * get_boss_frame(enem);
	if ((enem->text.rect.x + 80) < P_POS_X)
		enem->sign = 0;
	else
		enem->sign = SDL_FLIP_HORIZONTAL;
	ysort(NULL, text, &enem->text.rect, &enem->frame, NULL, 0, enem->sign, 0);
}

void	anim_brown_enem(t_enemy *enem, t_graphics *all, t_tex text)
{
	int	frame = enem->frc / 10;

	if (stay_put == 0)
	{
		enem->frc++;
		if (enem->frc == 60)
			enem->frc = 0;
	}
	if (place_meeting(screen, enem->text.rect) == 0)
		return ;
	enem->on_screen = 1;
	int	x = enem->text.rect.x - 40;
	int	s = enem->text.rect.x;
	enem->frame.x = 40 * frame;
	if (enem->text.rect.x > P_POS_X)
		enem->sign = 0;
	else
	{
		enem->text.rect.x = x;
		enem->sign = SDL_FLIP_HORIZONTAL;
	}
	ysort(NULL, text, &enem->text.rect, &enem->frame, NULL, 0, enem->sign, 0);
	enem->text.rect.x = s;
}

void	anim_crab_enem(t_enemy *enem, t_graphics *all, t_tex text)
{
	int	frame = enem->frc / 5;

	if (stay_put == 0)
	{
		enem->frc++;
		if (enem->frc == 40)
			enem->frc = 0;
	}
	if (place_meeting(screen, enem->text.rect) == 0)
		return ;
	enem->on_screen = 1;
	int	x = enem->text.rect.x + 20;
	int	s = enem->text.rect.x;
	enem->frame.x = 200 * frame;
	if ((enem->text.rect.x + 146) < P_POS_X)
		enem->sign = 0;
	else
	{
		enem->text.rect.x = x;
		enem->sign = SDL_FLIP_HORIZONTAL;
	}
	ysort(NULL, text, &enem->text.rect, &enem->frame, NULL, 0, enem->sign, 0);
	enem->text.rect.x = s;
}

void	anim_minotaur_enem(t_enemy *enem, t_graphics *all, t_tex text)
{
	int	frame = enem->frc / 5;

	if (stay_put == 0)
	{
		enem->frc++;
		if (enem->frc == 40)
			enem->frc = 0;
	}
	if (place_meeting(screen, enem->text.rect) == 0)
		return ;
	enem->on_screen = 1;
	int	x = enem->text.rect.x - 30;
	int	s = enem->text.rect.x;
	enem->frame.x = 180 * frame;
	if ((enem->text.rect.x + 100) < P_POS_X)
		enem->sign = 0;
	else
	{
		enem->text.rect.x = x;
		enem->sign = SDL_FLIP_HORIZONTAL;
	}
	ysort(NULL, text, &enem->text.rect, &enem->frame, NULL, 0, enem->sign, 0);
	enem->text.rect.x = s;
}

void	anim_red_frog_enem(t_enemy *enem, t_graphics *all, t_tex text)
{
	int	frame = enem->frc / 5;

	if (stay_put == 0)
	{
		enem->frc++;
		if (enem->frc == 40)
			enem->frc = 0;
	}
	if (place_meeting(screen, enem->text.rect) == 0)
		return ;
	enem->on_screen = 1;
	int	x = enem->text.rect.x;
	int	s = enem->text.rect.x;
	enem->frame.x = 190 * frame;
	if ((enem->text.rect.x + 90) < P_POS_X)
		enem->sign = 0;
	else
	{
		enem->text.rect.x = x;
		enem->sign = SDL_FLIP_HORIZONTAL;
	}
	ysort(NULL, text, &enem->text.rect, &enem->frame, NULL, 0, enem->sign, 0);
	enem->text.rect.x = s;
}

void	anim_scorpion_enem(t_enemy *enem, t_graphics *all, t_tex text)
{
	int	frame = enem->frc / 5;

	if (stay_put == 0)
	{
		enem->frc++;
		if (enem->frc == 40)
			enem->frc = 0;
	}
	if (place_meeting(screen, enem->text.rect) == 0)
		return ;
	enem->on_screen = 1;
	int	x = enem->text.rect.x + 30;
	int	s = enem->text.rect.x;
	enem->frame.x = 190 * frame;
	if ((enem->text.rect.x + 110) < P_POS_X)
		enem->sign = 0;
	else
	{
		enem->text.rect.x = x;
		enem->sign = SDL_FLIP_HORIZONTAL;
	}
	ysort(NULL, text, &enem->text.rect, &enem->frame, NULL, 0, enem->sign, 0);
	enem->text.rect.x = s;
}

void	choose_enem_anim_function(t_enemy *enem, t_graphics *all, t_tex text)
{
	void	(*anim_funct[9])(t_enemy *enem, t_graphics *all, t_tex text) = {anim_zomb, anim_red_enemy, anim_annoying, anim_boss, anim_brown_enem, anim_crab_enem, anim_minotaur_enem, anim_red_frog_enem, anim_scorpion_enem};
	
	(anim_funct[enem->type - 1](enem, all, text));
}
