
#include "../top_down.h"

int	point_on_map(double x, double y)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		return (1);
	return (0);
}

int	possible_move(SDL_Rect enem, SDL_Rect hbox, t_vec dir)
{
	if (dir.x > 0 && dir.y > 0) // bottom right of screen
	{
		if (enem.x > hbox.x || enem.y > hbox.y
			|| place_meeting(enem, hbox) == 0)
				return (1);
	}
	else if (dir.x < 0 && dir.y > 0) // bottom left
	{
		if (enem.x < hbox.x || enem.y > hbox.y
			|| place_meeting(enem, hbox) == 0)
			return (1);
	}
	else if (dir.x > 0 && dir.y < 0) // top right
	{
		if (enem.x > hbox.x || enem.y < hbox.y
			|| place_meeting(enem, hbox) == 0)
			return (1);
	}
	else if (dir.x < 0 && dir.y < 0) // top left
	{
		if (enem.x < hbox.x || enem.y < hbox.y
			|| place_meeting(enem, hbox) == 0)
			return (1);
	}
	return (0);
}

int	possible_boss_move(SDL_Rect hbox, SDL_Rect jbox, int curr, int diff)
{
	if (place_meeting(hbox, jbox))
	{
		if (diff < curr)
			return (1);
	}
	return (0);
}

void	move_enemy(t_enemy *enem, int i, t_vec f_pos)
{
	int			j = 0;
	SDL_Rect	hbox = create_move_hbox(&enem[i], f_pos);

	while (j < E_COUNT)
	{
		if (j != i && enem[j].type != 0)
		{
			if (enem[i].type == 3)
			{
				if (enem[j].type == 3 && possible_move(enem[j].hbox, hbox, enem[i].dir) == 0)
					return ;
			}
			else if (enem[i].type == 4)
			{
				if (enem[j].type == 4 && possible_boss_move(hbox, enem[j].hbox, i, j))
					return ;
			}
			else if (possible_move(enem[j].hbox, hbox, enem[i].dir) == 0)
				return ;
		}
		j++;
	}
	enem[i].pos.x = f_pos.x;
	enem[i].pos.y = f_pos.y;
}

void	calculate_new_vec(t_enemy *enem)
{
	t_vec	temp;
	double	len;

	temp.x = enem->pos.x - P_POS_X;
	temp.y = enem->pos.y - P_POS_Y;
	len = sqrt(temp.x * temp.x + temp.y * temp.y);
	enem->dir.x = temp.x / len;
	enem->dir.y = temp.y / len;
	enem->on_screen = 0;
}

void	respawn_same_enemy(t_enemy *enem, int i, t_text_enemy text)
{
	if (enem[i].type == 4)
	{
		boss_spawner(enem, &text, NULL, enem[i].hp, enem[i].life_time);
		enem[i].type = 0;
	}
	else if (check_the_space_to_spawn(enem, i))
		calculate_new_vec(&enem[i]);
}

int		can_respawn(t_enemy *enem, int i, double len)
{
	if (enem[i].type != 3 && ((enem[i].on_screen == 1 && len > 1200) || len > 1700))
		return (1);
	return (0);
}

void	get_temp_vec(t_enemy *enem, t_vec *temp)
{
	switch (enem->type)
	{
		case (4):
			temp->x = (enem->pos.x + (enem->text.rect.w / 2.38)) - P_POS_X;
			temp->y = (enem->pos.y + (enem->hbox.h / 2)) - P_POS_Y;
			return ;
		case (6):
			temp->x = (enem->pos.x + (enem->text.rect.w / 2)) - P_POS_X;
			temp->y = (enem->pos.y + (enem->hbox.h / 2)) - P_POS_Y;
			return ;
		case (7):
			temp->x = (enem->pos.x + 95) - P_POS_X;
			temp->y = (enem->pos.y + 90) - P_POS_Y;
			return ;
		case (8):
			temp->x = (enem->pos.x + 95) - P_POS_X;
			temp->y = (enem->pos.y + 65) - P_POS_Y;
			return ;
		case (9):
			temp->x = (enem->pos.x + 105) - P_POS_X;
			temp->y = (enem->pos.y + 50) - P_POS_Y;
			return ;
	}
	temp->x = (enem->pos.x) - P_POS_X;
	temp->y = (enem->pos.y) - P_POS_Y;
}

void	dir_and_len_to_h_box(t_enemy *enem, int i, t_text_enemy text)
{
	t_vec	temp;
	t_vec	f_pos;
	double	len;
	double	spd = real_speed;

	get_temp_vec(&enem[i], &temp);
	len = sqrt(temp.x * temp.x + temp.y * temp.y);
	p_hit(len, enem[i].hbox, enem[i].type, &enem[i]);
	if (can_respawn(enem, i, len))
		respawn_same_enemy(enem, i, text);
	else
	{
		enem[i].dir.x = temp.x / len;
		enem[i].dir.y = temp.y / len;
	}
	f_pos.x = enem[i].pos.x - (enem[i].dir.x * (spd / enem[i].enem_speed));
	f_pos.y = enem[i].pos.y - (enem[i].dir.y * (spd / enem[i].enem_speed));
	move_enemy(enem, i, f_pos);
}

void	move_main(t_enemy *enem, int i, t_text_enemy text)
{
	dir_and_len_to_h_box(enem, i, text);
}
