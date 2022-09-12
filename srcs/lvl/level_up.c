
#include "../top_down.h"
#define MUSIC_CHANNEL 21

void	just_add_to_progress(unsigned int *progress, int amount)
{
	*progress += amount;
}

uint8_t	make_lvl_progress(int *width, int progress, int lvl_bar, int sign)
{
	static unsigned int	check = 0;
	static double		interval;
	static unsigned int	now = 0;

	if (sign == START_INIT)
	{
		check = 0;
		now = 0;
		return (0);
	}
	if (check != lvl_bar)
	{
		check = lvl_bar;
		interval = 800.f / (double)lvl_bar;
	}
	*width = interval * progress;
	if (*width >= 800 || now == 1)
	{
		if (now == 1)
		{
			now = 0;
			return (1);
		}
		now = 1;
	}
	return (0);
}

void	draw_bar(t_graphics *all, t_tr full, t_tr empty)
{
	make_curr_graph(all, empty.text, &empty.rect, NULL, NULL, 0, 0);
	make_curr_graph(all, full.text, &full.rect, NULL, NULL, 0, 0);
	put_number_to_screen(all, lvl_up_counter, 1046, 766, 2);
}

int		big_lvl_manage(int count)
{
	if (count < 50)
		return (7400);
	if (count < 60)
		return (7600);
	if (count < 70)
		return (7800);
	if (count < 74)
		return (8100);
	if (count < 77)
		return (8600);
	if (count < 80)
		return (9000);
	if (count < 86)
		return (11000);
	if (count < 90)
		return (14000);
	if (count < 93)
		return (20000);
	if (count < 96)
		return (100000);
	return (300000);
}

void	update_progress_on_lvl_up(int *width, unsigned int *progress, unsigned int *lvl_bar, int sign)
{
	static double	bigger = 1.3;

	if (sign == START_INIT)
	{
		bigger = 1.3;
		return ;
	}
	*width = 0;
	*progress = *progress - *lvl_bar;
	if ((*progress - *lvl_bar) < 0)
		*progress = 0;
	*lvl_bar = *lvl_bar * bigger;
	if (*lvl_bar > 7400)
		*lvl_bar = big_lvl_manage(lvl_up_counter);
	lvl_up_counter += 1;
	switch (lvl_up_counter)
	{
		case 7:
			bigger = 1.2;
			break ;
		case 18:
			bigger = 1.1;
			break ;
		case 25:
			bigger = 1.05;
			break ;
		case 33:
			bigger = 1.3;
			break ;
	}
}

int	lvl_card_x_if(int index)
{
	if (index == 5 && insta_kill_active != 0)
		return (1);
	if (index == 11 && dead_whale_active != 0)
		return (1);
	return (0);
}

void	put_chosen_upgrades_to_screen(t_itr one, t_itr two, t_itr three, SDL_Renderer *rend)
{
	SDL_Rect	fr;

	fr.x = 0;
	fr.y = 0;
	fr.w = 200;
	fr.h = 360;
	if (lvl_card_x_if(one.index))
		fr.x = 200;
	SDL_RenderCopy(rend, one.tr.text.text, &fr, &one.tr.rect);
	fr.x = 0;
	if (lvl_card_x_if(two.index))
		fr.x = 200;
	SDL_RenderCopy(rend, two.tr.text.text, &fr, &two.tr.rect);
	fr.x = 0;
	if (lvl_card_x_if(three.index))
		fr.x = 200;
	SDL_RenderCopy(rend, three.tr.text.text, &fr, &three.tr.rect);
}

uint8_t	pick_upgrade(t_itr one, t_itr two, t_itr three, int x, int y, int click)
{
	if (point_meeting(x, y, one.tr.rect) && click == 1)
		return (one.index + 1);
	if (point_meeting(x, y, two.tr.rect) && click == 1)
		return (two.index + 1);
	if (point_meeting(x, y, three.tr.rect) && click == 1)
		return (three.index + 1);
	return (0);
}

void	make_x_for_rect(SDL_Rect *one, SDL_Rect *two, SDL_Rect *three)
{
	one->x = 250;
	two->x = 550;
	three->x = 850;
}

void	exhaust_init(int *exhaust)
{
	int	i = 0;

	while (i < 13)
	{
		exhaust[i] = 0;
		i++;
	}
}

void	choose_upgrade(t_level_up *lvl, SDL_Renderer *rend, t_tr *cursor, t_keys *keys, Mix_Chunk *card, t_graphics *all, int sign)
{
	int			x, y;
	static int	exhaust[13] = { 0 };
	clock_t		start, end;
	SDL_Event	event = { 0 };
	t_itr		one, two, three;
	uint8_t		bool = 0;
	int			iters = 0;

	if (sign == START_INIT)
		return (exhaust_init(exhaust));
	choose_one_two_three(&one, &two, &three, lvl, exhaust);
	make_x_for_rect(&one.tr.rect, &two.tr.rect, &three.tr.rect);
	bigger_smaller_rect(NULL, NULL, NULL, 0, 0, 1);
	stay_put = 1;
	while (bool == 0)
	{
		start = clock();
		keys->click = 0;
		ft_keys(event, keys);
		SDL_RenderClear(rend);
		SDL_GetMouseState(&x, &y);
		put_images_to_screen(rend, all);
		if (iters == 20)
			bool = pick_upgrade(one, two, three, x, y, keys->click);
		bigger_smaller_rect(&one.tr.rect, &two.tr.rect, &three.tr.rect, x, y, 0);
		put_chosen_upgrades_to_screen(one, two, three, rend);
		lvl_c_to_screen(rend, *cursor, x, y);
		SDL_RenderPresent(rend);
		if (iters < 20)
			iters++;
		end = clock();
		SDL_Delay(figure_the_delay(start, end));
	}
	upgrade_chosen_attribute(bool, exhaust, lvl->amount);
	Mix_PlayChannel(1, card_choosing_soundeffect, 0);
	stay_put = 0;
	keys->click = 0;
}

//this function is called from orb.c file from orb_hit function and from main
void	level_up_main(t_level_up *lvl, int amount, SDL_Renderer *rend,
						t_tr *cursor, t_keys *keys, t_lvl_audio *lvl_up, t_graphics *all, int sign)
{
	static unsigned int	lvl_bar = 10;
	static unsigned int	progress = 0;

	if (sign == START_INIT)
	{
		lvl_bar = 10;
		progress = 0;
		make_lvl_progress(NULL, 0, 0, START_INIT);
		update_progress_on_lvl_up(NULL, NULL, NULL, START_INIT);
		return (choose_upgrade(NULL, NULL, NULL, NULL, NULL, NULL, START_INIT));
	}
	if (lvl == NULL)
		return (just_add_to_progress(&progress, amount));
	if (egg_lvl_up_time == 1)
	{
		egg_lvl_up_time = 0;
		Mix_Pause(MUSIC_CHANNEL);
		egg_amount_counter += 1;
		egg_level_screen(rend, *cursor, keys, all);
	}
	if (make_lvl_progress(&lvl->bar[0].rect.w, progress, lvl_bar, 0))
	{
		Mix_Pause(MUSIC_CHANNEL);
		Mix_PlayChannel(0, lvl_up_instance_soundeffect, 0);
		choose_upgrade(lvl, rend, cursor, keys, lvl_up->card, all, 0);
		update_progress_on_lvl_up(&lvl->bar[0].rect.w, &progress, &lvl_bar, 0);
	}
	Mix_Resume(MUSIC_CHANNEL);
}
