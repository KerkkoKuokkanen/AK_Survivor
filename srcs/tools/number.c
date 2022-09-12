
#include "../top_down.h"

int		get_num_or_null(int *num, int *num_save, int make_big)
{
	if (num == NULL)
		return (0);
	if (*num == 0)
		return (1);
	*num_save = *num;
	return (0);
}

int		get_make_big(int *make_big, int save)
{
	if (*make_big != (-1))
		return (0);
	int	count = 1;
	while (count <= save)
		count *= 10;
	*make_big = (count / 10);
	return (0);
}

int		get_ret(int *make_big, int *save)
{
	int	sav = *save, big = *make_big;
	int	ret = 0;

	if (big == (-1))
		return (-1);
	if (sav == 0 && big != (-1))
	{
		big /= 10;
		if (big == 0)
		{
			*make_big = (-1);
			return (0);
		}
		*make_big = big;
		return (ret);
	}
	sav = sav % big;
	ret = (*save / *make_big);
	*save = sav;
	*make_big = (big / 10);
	if (big < 10)
		*make_big = (-1);
	return (ret);
}

int		numtok(int *num)
{
	static int	make_big = (-1);
	static int	num_save = 0;

	if (make_big == (-1) && num == NULL)
		return (-1);
	if (get_num_or_null(num, &num_save, make_big))
		return (0);
	get_make_big(&make_big, num_save);
	return (get_ret(&make_big, &num_save));
}

void	put_number_to_screen(t_graphics *all, int number, int x, int y, int size)
{
	int	index_value = 0;
	int	count = 0;
	int	text_size = 8 * size;
	SDL_Rect	dest = {x, y, text_size, text_size};
	SDL_Rect	frame = {0, 0, 16, 16};

	while (index_value != (-1))
	{
		if (count == 0)
			index_value = numtok(&number);
		else
			index_value = numtok(NULL);
		dest.x = (x + (text_size * count));
		if (index_value != (-1))
		{
			frame.x = (16 * index_value);
			make_curr_graph(all, numbers_texture_sheet, &dest, &frame, NULL, 0, 0);
		}
		count++;
	}
}

void	rend_put_number_to_screen(SDL_Renderer *rend, int number, int x, int y, int size)
{
	int	index_value = 0;
	int	count = 0;
	int	text_size = 8 * size;
	SDL_Rect	dest = {x, y, text_size, text_size};
	SDL_Rect	frame = {0, 0, 16, 16};

	while (index_value != (-1))
	{
		if (count == 0)
			index_value = numtok(&number);
		else
			index_value = numtok(NULL);
		dest.x = (x + (text_size * count));
		if (index_value != (-1))
		{
			frame.x = (16 * index_value);
			SDL_RenderCopy(rend, numbers_texture_sheet.text, &frame, &dest);
		}
		count++;
	}
}
