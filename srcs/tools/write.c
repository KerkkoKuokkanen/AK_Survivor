
#include "../top_down.h"
#define NORMAL_FONT_SIZE 5

// makes the amount of distance to the next character
void	get_the_character_jump(char c, SDL_Rect *dest, int index, int size)
{
	if (c == 'i' || c == ':')
		dest->x += (2 * size);
	else if (c == 'l' || c == 't' || c == 'v' || c == 'y' || c == 'x')
		dest->x += (4 * size);
	else if (c == 'm' || c == 'w')
		dest->x += (6 * size);
	else if (c == ' ')
		dest->x += (1 * size);
	else
		dest->x += (5 * size);
}

int	get_frame(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (5 * (c - 65));
	if (c >= 'a' && c <= 'z')
		return (5 * (c - 97));
	if (c == 58)
		return (145);
	if (c == ' ')
		return (200);
	return (0);
}

void	put_text_to_screen(t_graphics *all, int x_start, int y_start, char *text, unsigned const int text_size, const int font)
{
	int			i = 0;
	int			size = NORMAL_FONT_SIZE * text_size;
	if (text_size == 0)
		size = NORMAL_FONT_SIZE;
	int			cast_jump = size / 5;
	SDL_Rect	dest = {x_start, y_start, size, size};
	SDL_Rect	frame = {0, 0, 5, 5};

	if (font == 1)
		frame.y = 5;
	while (text[i] != '\0')
	{
		frame.x = get_frame(text[i]);
		make_curr_graph(all, alphabet_full_texture, &dest, &frame, NULL, 0, 0);
		get_the_character_jump(text[i], &dest, i, cast_jump);
		i++;
	}
}

void	rend_put_text_to_screen(SDL_Renderer *rend, int x_start, int y_start, char *text, unsigned const int text_size, const int font)
{
	int			i = 0;
	int			size = NORMAL_FONT_SIZE * text_size;
	if (text_size == 0)
		size = NORMAL_FONT_SIZE;
	int			cast_jump = size / 5;
	SDL_Rect	dest = {x_start, y_start, size, size};
	SDL_Rect	frame = {0, 0, 5, 5};

	if (font == 1)
		frame.y = 5;
	while (text[i] != '\0')
	{
		frame.x = get_frame(text[i]);
		SDL_RenderCopy(rend, alphabet_full_texture.text, &frame, &dest);
		get_the_character_jump(text[i], &dest, i, cast_jump);
		i++;
	}
}
