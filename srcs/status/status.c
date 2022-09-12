
#include "../top_down.h"
#define MUSIC_CHANNEL 21
#define CARDS 14

void	put_lvl_number_to_screen(SDL_Renderer *rend, t_tex *nums, unsigned const int number, int x, int y)
{
	SDL_Rect	dest = {x, y, 16, 16};
	SDL_Rect	frame = {0, 0, 16, 14};
	int			curr;
	if (number < 10)
	{
		frame.x = 16 * number;
		SDL_RenderCopy(rend, nums->text, &frame, &dest);
		return ;
	}
	curr = get_the_num_from_time(number, 0);
	frame.x = 16 * curr;
	SDL_RenderCopy(rend, nums->text, &frame, &dest);
	dest.x += 16;
	curr = get_the_num_from_time(number, 1);
	frame.x = 16 * curr;
	SDL_RenderCopy(rend, nums->text, &frame, &dest);
}

void	show_lvl_amount(SDL_Renderer *rend, t_textures *text, int amount, int x, int y)
{
	if (amount == (-1))
		return (rend_put_text_to_screen(rend, (x + 10), (y - 25), "max", 3, 1));
	put_lvl_number_to_screen(rend, &text->nums, amount, (x + 10), (y - 30));
}

void	put_lvl_cards_to_screen(SDL_Renderer *rend, t_textures *text)
{
	int			i = 0;
	SDL_Rect	dest = {142, 120, 100, 180};
	SDL_Rect	frame = {0, 0, 200, 360};

	while (i < CARDS)
	{
		if (i == 7)
		{
			dest.x = 142;
			dest.y += 260;
		}
		if (i != 0 && i != 7)
			dest.x += 150;
		show_lvl_amount(rend, text, text->lvl.amount[i], dest.x, dest.y);
		SDL_RenderCopy(rend, text->lvl.lvlup_tex[i].text.text, &frame, &dest);
		i++;
	}
}

void	damage_ups_to_screen(SDL_Renderer *rend)
{
	SDL_Rect	dest = {540, 625, 32, 32};
	rend_put_text_to_screen(rend, 300, 630, "damage ups", 5, 1);
	SDL_RenderCopy(rend, double_dot_thexture_sprite.text, NULL, &dest);
	rend_put_number_to_screen(rend, egg_amount_counter, 580, 625, 4);
	rend_put_text_to_screen(rend, 658, 630, "out of", 5, 1);
	rend_put_number_to_screen(rend, 14, 810, 625, 4);
}

void	show_player_status(t_graphics *all, SDL_Renderer *rend, t_keys *keys, t_textures *text, t_tr *cursor)
{
	SDL_Event	event = { 0 };
	clock_t		start, end;
	int			x, y;

	if (keys->tab == 0)
		return ;
	Mix_Pause(MUSIC_CHANNEL);
	while (keys->tab == 1)
	{
		start = clock();
		SDL_RenderClear(rend);
		ft_keys(event, keys);
		SDL_GetMouseState(&x, &y);
		put_images_to_screen(rend, all);
		SDL_RenderCopy(rend, text->off_color_status.text, NULL, NULL);
		put_lvl_cards_to_screen(rend, text);
		damage_ups_to_screen(rend);
		lvl_c_to_screen(rend, *cursor, x, y);
		SDL_RenderPresent(rend);
		end = clock();
		SDL_Delay(figure_the_delay(start, end));
	}
	Mix_Resume(MUSIC_CHANNEL);
}
