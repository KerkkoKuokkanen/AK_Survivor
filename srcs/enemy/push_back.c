
#include "../top_down.h"

void	move_enem_back(t_enemy *enem, int curr)
{
	SDL_Rect	hbox;
	t_vec		pos;
	t_vec		temp_dir;
	uint8_t		bool = 0;
	int			i = 0;
	int			amount = 0;
	int			j;

	hbox.w = enem[curr].hbox.w;
	hbox.h = enem[curr].hbox.h;
	temp_dir.x = enem[curr].dir.x * (-1);
	temp_dir.y = enem[curr].dir.y * (-1);
	while (i < enem[curr].push_back_amount)
	{
		pos.x = enem[curr].pos.x - temp_dir.x * (i + amount);
		pos.y = enem[curr].pos.y - temp_dir.y * (i + amount);
		hbox.x = pos.x;
		hbox.y = pos.y;
		j = 0;
		while (j < E_COUNT)
		{
			if (enem[curr].type == 3)
				break ;
			if (enem[j].type != 0 && j != curr)
			{
				if (possible_move(enem[j].hbox, hbox, temp_dir) == 0)
				{
					bool = 1;
					break ;
				}
			}
			j++;
		}
		if (bool == 1)
			break ;
		i++;
		amount += 2;
	}
	enem[curr].pos = pos;
//	enem[curr].hbox.x = enem[curr].pos.x;
//	enem[curr].hbox.y = enem[curr].pos.y;
}

void	push_back_main(t_enemy *enem, int curr)
{
	if (enem[curr].got_shot == 1)
	{
		enem[curr].push.duration = 8;
		enem[curr].push.dir = enem[curr].dir;
		enem[curr].got_shot = 0;
	}
	move_enem_back(enem, curr);
	if (enem[curr].push.duration > 0)
		enem[curr].push.duration--;
}
