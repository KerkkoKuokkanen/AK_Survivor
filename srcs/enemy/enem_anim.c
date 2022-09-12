
#include "../top_down.h"

void	choose_enem_anim(t_enemy *enem, t_graphics *all)
{
	t_tex	text;

	enem->text.rect.x = enem->pos.x;
	enem->text.rect.y = enem->pos.y;
	screen_shaker(&enem->text.rect.x, &enem->text.rect.y);
	if (enem->got_hit > 0)
	{
		text = enem->hit_text;
		enem->got_hit--;
	}
	else
		text = enem->text.text;
	choose_enem_anim_function(enem, all, text);
}

void	sort_enemy_array(t_enemy *enem, t_graphics *all)
{
	int	i = 0;

	while (i < E_COUNT)
	{
		if (enem[i].type != 0)
			choose_enem_anim(&enem[i], all);
		i++;
	}
}
