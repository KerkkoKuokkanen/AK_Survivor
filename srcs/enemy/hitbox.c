
#include "../top_down.h"

void	update_enem_hbox(t_enemy *enem)
{
	switch (enem->type)
	{
		case (4):
			enem->hbox.y = enem->text.rect.y + 30;
			if (enem->sign == 1)
			{
				enem->hbox.x = enem->text.rect.x + 60;
				enem->hbox.w = 80;
				return ;
			}
			enem->hbox.x = enem->text.rect.x + 40;
			enem->hbox.w = 100;
			return ;
		case (6):
			enem->hbox.y = enem->text.rect.y + 35;
			enem->hbox.x = enem->text.rect.x + 130;
			return ;
		case (7):
			enem->hbox.y = enem->text.rect.y + 100;
			enem->hbox.x = enem->text.rect.x + 100;
			return ;
		case (8):
			enem->hbox.y = enem->text.rect.y + 60;
			enem->hbox.x = enem->text.rect.x + 70;
			return ;
		case (9):
			enem->hbox.y = enem->text.rect.y + 50;
			enem->hbox.x = enem->text.rect.x + 105;
			return ;
	}
	enem->hbox.y = enem->text.rect.y;
	enem->hbox.x = enem->text.rect.x;
}

SDL_Rect	create_move_hbox(t_enemy *enem, t_vec fpos)
{
	SDL_Rect	hbox;

	hbox.w = enem->hbox.w;
	hbox.h = enem->hbox.h;
	hbox.x = fpos.x;
	hbox.y = fpos.y;
	switch (enem->type)
	{
		case (6):
			hbox.x = fpos.x + 130;
			hbox.y = fpos.y + 35;
			break ;
		case (7):
			hbox.x = fpos.x + 100;
			hbox.y = fpos.y + 100;
			break ;
		case (8):
			hbox.y = fpos.y + 70;
			hbox.x = fpos.x + 60;
			break ;
		case (9):
			hbox.x = fpos.x + 105;
			hbox.y = fpos.y + 50;
			break ;
	}
	return (hbox);
}
