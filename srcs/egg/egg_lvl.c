
#include "../top_down.h"

int		upgrade_chosen(const int x, const int y, const SDL_Rect upgrade, const int click)
{
	if (point_meeting(x, y, upgrade) && click == 1)
		return (1);
	return (0);
}

void	make_rect_bigger(SDL_Rect *uprgade, const int x, const int y, const int sign)
{
	static int	size = 0;

	if (sign == 0)
	{
		size = 0;
		return ;
	}
	if (point_meeting(x, y, *uprgade) && size < 5)
	{
		uprgade->x -= 2;
		uprgade->y -= 4;
		uprgade->w += 4;
		uprgade->h += 8;
		size += 1;
	}
	else if (point_meeting(x, y, *uprgade) == 0 && size > 0)
	{
		uprgade->x += 2;
		uprgade->y += 4;
		uprgade->w -= 4;
		uprgade->h -= 8;
		size -= 1;
	}
}

void	egg_level_screen(SDL_Renderer *rend, t_tr cursor, t_keys *keys, t_graphics *all)
{
	int			x, y, iters = 0;
	clock_t		start, end;
	SDL_Event	event = {0};
	SDL_Rect	upgrade = {550, 200, 200, 360};
	uint8_t		bool = 0;

	Mix_PlayChannel(0, lvl_up_instance_soundeffect, 0);
	make_rect_bigger(NULL, 0, 0, 0);
	stay_put = 1;
	while (bool == 0)
	{
		start = clock();
		keys->click = 0;
		ft_keys(event, keys);
		SDL_RenderClear(rend);
		SDL_GetMouseState(&x, &y);
		put_images_to_screen(rend, all);
		if (upgrade_chosen(x, y, upgrade, keys->click) && iters == 20)
			bool = 1;
		make_rect_bigger(&upgrade, x, y, 1);
		SDL_RenderCopy(rend, dmg_upgrade_tex.text, NULL, &upgrade);
		lvl_c_to_screen(rend, cursor, x, y);
		SDL_RenderPresent(rend);
		if (iters < 20)
			iters++;
		end = clock();
		SDL_Delay(figure_the_delay(start, end));
	}
	SDL_RenderClear(rend);
	dmg_increase = 1;
	bullet_damage += 16;
	Mix_PlayChannel(1, card_choosing_soundeffect, 0);
	stay_put = 0;
	keys->click = 0;
}
