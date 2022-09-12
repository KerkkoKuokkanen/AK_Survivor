
#include "../top_down.h"

int		len_to_nearest_enem(t_enemy *enem, int curr, int i)
{
	int	x, y;

	x = (enem[curr].hbox.x) - (enem[i].hbox.x);
	y = (enem[curr].hbox.y) - (enem[i].hbox.y);
	return (sqrt(x * x + y * y));
}

int		len_to_nearest_enem_and_angle(t_enemy *enem, int curr, int i, int *deg)
{
	t_vec	v1, v2;
	double	rad;

	v1.y = 0;
	v2.x = (enem[curr].hbox.x + (enem[curr].hbox.w / 2)) - (enem[i].hbox.x + (enem[i].hbox.w / 2));
	v2.y = (enem[curr].hbox.y + (enem[curr].hbox.h / 2)) - (enem[i].hbox.y + (enem[i].hbox.h / 2));
	if (enem[curr].hbox.y > enem[i].hbox.y)
	{
		v1.x = 1;
		rad = calc_a(v2, v1);
		rad -= PI;
	}
	else
	{
		v1.x = (-1);
		rad = calc_a(v2, v1);
	}
	*deg = degree(rad);
	return (sqrt(v2.x * v2.x + v2.y * v2.y));
}

void	create_shock(t_enemy *enem, int curr, t_shock_anim *shocked, int i)
{
	int j = 0;

	while (shocked[j].in_use != 0 && j < 9000)
		j++;
	if (j >= 9000)
		return ;
	shocked[j].in_use = 1;
	shocked[j].source = curr;
	shocked[j].victim = i;
	shocked[j].time = 0;
	Mix_PlayChannel(9, shock.shock_audio, 0);
}

void	make_the_shock(t_enemy *enem, int curr, t_shock_anim *shocked)
{
	int	count = 0;
	int	i = 0;
	int	len;

	while (i < E_COUNT)
	{
		if (enem[i].type != 0 && i != curr)
		{
			len = len_to_nearest_enem(enem, curr, i);
			if (len < SHOCK_RANGE)
			{
				create_shock(enem, curr, shocked, i);
				count++;
			}
		}
		if (count >= shock_active)
			break ;
		i++;
	}
}

void	manage_shock(t_shock_anim *shocked, t_graphics *all, t_enemy *enem, Mix_Chunk *death)
{
	if (shocked->time >= SHOCK_TIME ||
		enem[shocked->victim].type == 0 ||
		enem[shocked->source].type == 0)
	{
		if (enem[shocked->victim].type != 0)
		{
			enem[shocked->victim].got_hit = 5;
			if (bullet_damage / 3 == 0)
				enem[shocked->victim].hp -= 1;
			else
				enem[shocked->victim].hp -= bullet_damage / 3;
			if (enem[shocked->victim].hp <= 0)
			{
				enem_kill_counter(&enem[shocked->victim]);
				orb_main(enem, NULL, NULL, NULL, shocked->victim);
				particle_main(&enem[shocked->victim], NULL, NULL, shocked->victim);
				enem[shocked->victim].type = 0;
				Mix_PlayChannel(2, death, 0);
				dead_whale_explosion_main(enem, shocked->victim, NULL, 0, NULL, NULL);
				dagger_main(enem, shocked->victim, NULL, NULL, NULL);
				if (s_shake_active != 2)
					s_shake_active = 1;
				screen_shake_amount = 1;
			}
		}
		shocked->in_use = 0;
		return ;
	}
	shocked->time++;

	int			deg;
	SDL_Rect	shock_dest;
	SDL_Rect	shock_frame;
	SDL_Point	rot = {0, 10};
	shock_dest.w = len_to_nearest_enem_and_angle(enem, shocked->source, shocked->victim, &deg);
	if (shock_dest.w > SHOCK_RANGE)
	{
		shocked->in_use = 0;
		return ;
	}
	shock_dest.h = 20;
	shock_dest.x = enem[shocked->source].hbox.x + (enem[shocked->source].hbox.w / 2);
	shock_dest.y = enem[shocked->source].hbox.y + (enem[shocked->source].hbox.h / 2);
	shock_frame.x = 0;
	shock_frame.y = 20 * (shocked->time / 2);
	shock_frame.w = 200;
	shock_frame.h = 20;
	if (place_meeting(shock_dest, screen))
		make_curr_graph(all, shock.shock_tex, &shock_dest, &shock_frame, &rot, deg, 0);
}

void	animate_shock(t_shock_anim *shocked, t_graphics *all, t_enemy *enem, Mix_Chunk *death)
{
	int	i = 0;

	while (i < 9000)
	{
		if (shocked[i].in_use == 1)
			manage_shock(&shocked[i], all, enem, death);
		i++;
	}
}

void	shock_the_enemies(t_enemy *enem, t_graphics *all, Mix_Chunk *death, int curr, int sign)
{
	static t_shock_anim	shocked[9000] = { };

	if (sign == START_INIT)
	{
		bzero(shocked, sizeof(t_shock) * 9000);
		return ;
	}
	if (shock_active == 0)
		return ;
	if (sign == 1)
		make_the_shock(enem, curr, shocked);
	else
		animate_shock(shocked, all, enem, death);
}
