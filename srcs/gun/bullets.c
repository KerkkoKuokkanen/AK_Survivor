
#include "../top_down.h"

void	init_bullets(t_bullets *bullets)
{
	int	i = 0;

	bzero(bullets, sizeof(t_bullets) * BULLET_COUNT);
	while (i < BULLET_COUNT)
	{
		bullets[i].tru = 0;
		bullets[i].hbox.w = 16;
		bullets[i].hbox.h = 16;
		bullets[i].type = 0;
		i++;
	}
}

void	create_bullet_array(t_bullets *bullets, t_shot *shot)
{
	shot->delay = 0;
	shot->reload = 0;
	shot->shot_count = 0;
	shot->time_to_shoot = 0;
	init_bullets(bullets);
}

t_vec	make_the_shot_vec(t_vec pos, int x, int y)
{
	t_vec	svec;
	double	len;

	svec.x = pos.x - x;
	svec.y = pos.y - y;
	len = sqrt(svec.x * svec.x + svec.y * svec.y);
	svec.x /= len;
	svec.y /= len;
	return (svec);
}

void	shot_pos_edge_cases(int y, double ty, t_vec *pos)
{
	if (y > CENTER_Y)
	{
		if (angle == -90)
			pos->y -= ty;
		else
			pos->y += ty;
	}
	else
	{
		if (angle == -90)
			pos->y += ty;
		else
			pos->y -= ty;
	}
}

void	find_the_starting_pos(int x, int y, t_vec *pos)
{
	double	tx;
	double	ty;

	tx = 30 * cos(RAD * angle);
	ty = 30 * sin(RAD * angle);
	if (x == CENTER_X)
		return (shot_pos_edge_cases(y, ty, pos));
	if (x < CENTER_X)
	{
		pos->x -= tx;
		pos->y -= ty;
		return ;
	}
	pos->x += tx;
	pos->y += ty;
}

int	get_the_bullet_type()
{
	if (insta_kill_active == 0)
		return (0);
	int	random;
	int	correct = 1;
	int	range = 17;

	range -= insta_kill_active;
	random = rand() % range;
	if (random == correct)
		return (1);
	return (0);
}

int	create_shot(t_bullets *bullets, int x, int y)
{
	int	i = 0;

	while (bullets[i].tru == 1)
		i++;
	bullets[i].tru = 1;
	bullets[i].life_time = 0;
	bullets[i].type = get_the_bullet_type();
	bullets[i].pos.x = CENTER_X;
	bullets[i].pos.y = CENTER_Y;
	bullets[i].dir = make_the_shot_vec(bullets[i].pos, x, y);
	find_the_starting_pos(x, y, &bullets[i].pos);
	bullets[i].pos.y -= 8;
	bullets[i].pos.x -= 8;
	bullets[i].hbox.x = bullets[i].pos.x;
	bullets[i].hbox.y = bullets[i].pos.y;
	return (i);
}

void	iter_shot_struct(t_shot *shot, t_tr relaod_empty, t_tr reload_full, Mix_Chunk *reload, t_graphics *all)
{
	double		one_width;
	int			rest;
	static int	rr = 0;

	if (shot->delay > 0)
		shot->delay--;
	if (shot->reload > 0)
	{
		if (rr == 0)
			Mix_PlayChannel(8, reload, 0);
		one_width = 50.f / (double)reload_speed;
		rest = reload_speed - shot->reload;
		reload_full.rect.w = one_width * rest;
		make_curr_graph(all, relaod_empty.text, &relaod_empty.rect, NULL, NULL, 0, 0);
		make_curr_graph(all, reload_full.text, &reload_full.rect, NULL, NULL, 0, 0);
		shot->reload--;
		rr = 1;
		if (shot->reload == 0)
		{
			shot->shot_count = 0;
			rr = 0;
		}
	}
}

void	move_bullet(t_bullets *bullet)
{
	move_dest_from_player(&bullet->pos);
	bullet->pos.x -= bullet->dir.x * bullet_speed;
	bullet->pos.y -= bullet->dir.y * bullet_speed;
	bullet->hbox.x = bullet->pos.x;
	bullet->hbox.y = bullet->pos.y;
	screen_shaker(&bullet->hbox.x, &bullet->hbox.y);
}

void	check_life_time(t_bullets *bullet)
{
	if (bullet->life_time >= max_bullet_life)
		bullet->tru = 0;
	bullet->life_time++;
}

int	get_the_damage_on_hit(t_bullets *bullet)
{
	int	rage = 1;
	int	crit = 1;

	if (bullet->type == 1)
		crit = 2;
	if (rage_now > 0)
		rage = 2;
	if (bullet->type != 2)
		return (bullet_damage * rage * crit);
	int	ret = bullet_damage / 2;
	if (ret == 0)
		return (1 * rage);
	return (ret * rage);
}

int	check_if_bullet_hit_enemy(t_enemy *enem, t_bullets *bullet, Mix_Chunk **enem_death, int curr)
{
	int	i = 0;

	while (i < E_COUNT)
	{
		if (enem[i].type != 0 && place_meeting(enem[i].hbox, bullet[curr].hbox))
		{
			enem[i].hp -= get_the_damage_on_hit(&bullet[curr]);
			if (bullet[curr].type == 1)
				Mix_PlayChannel(17, critical_hit_soundeffect, 0);
			if (bullet[curr].type != 2)
				enem[i].got_shot = 1;
			enem[i].got_hit = 5;
			shock_the_enemies(enem, NULL, NULL, i, 1);
			bullet[curr].tru = 0;
			fractal_shot_creator(bullet, curr);
			if (enem[i].hp <= 0)
			{
				enem_kill_counter(&enem[i]);
				orb_main(enem, NULL, NULL, NULL, i);
				particle_main(&enem[i], NULL, NULL, i);
				enem[i].type = 0;
				Mix_PlayChannel(2, enem_death[0], 0);
				dead_whale_explosion_main(enem, i, NULL, 0, NULL, NULL);
				dagger_main(enem, i, NULL, NULL, NULL);
				bzero(&enem[i], sizeof(t_enemy));
				if (s_shake_active != 2)
					s_shake_active = 1;
				screen_shake_amount = 1;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_bullet_fr()
{
	static int	x = 0;

	if ((bullet_damage / 16) == 1)
		x = 0;
	if (dmg_increase == 1)
	{
		dmg_increase = 0;
		switch (bullet_damage / 16)
		{
			case 3:
				x = 32;
				break ;
			case 6:
				x = 64;
				break ;
			case 9:
				x = 96;
				break ;
			case 12:
				x = 128;
				break ;
			case 15:
				x = 160;
				break ;
		}
	}
	return (x);
}

void	bullet_iter_and_travel(t_bullets *bullets, t_graphics *all, t_tex bullet,
								t_enemy *enem, Mix_Chunk *hitmark, Mix_Chunk **enem_death)
{
	int	i = 0;

	shotti_sheet_fr.x = get_bullet_fr();
	while (i < BULLET_COUNT)
	{
		if (bullets[i].tru == 1)
		{
			move_bullet(&bullets[i]);
			if (check_if_bullet_hit_enemy(enem, bullets, enem_death, i))
				Mix_PlayChannel(4, hitmark, 0);
			check_life_time(&bullets[i]);
			if (place_meeting(screen, bullets[i].hbox))
			{
				if (bullets[i].type == 1)
					make_curr_graph(all, bullet, &bullets[i].hbox, &instakill_rect, NULL, 0, 0);
				else if (bullets[i].type != 2)
					make_curr_graph(all, bullet, &bullets[i].hbox, &shotti_sheet_fr, NULL, 0, 0);
				else
				{
					fractal_rect.x = bullets[i].hbox.x + 3;
					fractal_rect.y = bullets[i].hbox.y + 3;
					make_curr_graph(all, bullet, &fractal_rect, &shotti_sheet_fr, NULL, 0, 0);
				}
			}
		}
		i++;
	}
}

void	bullets_main(int x, int y, uint8_t *key, t_graphics *all, t_tex *bullet, t_enemy *enem,
						Mix_Chunk *gun_shoot, Mix_Chunk *hitmark, Mix_Chunk **enem_death, t_tex *mag, uint8_t *r_key,
						t_tr *reload_full, t_tr *reload_empty, Mix_Chunk *reload)
{
	static t_bullets	bullets[BULLET_COUNT];
	static t_shot		shot;

	if (reload_full == NULL)
		return (create_bullet_array(bullets, &shot));
	bullet_iter_and_travel(bullets, all, *bullet, enem, hitmark, enem_death);
	mag_main(shot.shot_count, *mag, all);
	iter_shot_struct(&shot, *reload_empty, *reload_full, reload, all);
	shot_happening = 0;
	egg_main(bullets, NULL, 1);
	if (*r_key == 1 && shot.reload == 0 && shot.shot_count != 0)
		shot.reload = reload_speed;
	if (*key == 0)
		return ;
	if (shot.reload == 0 && shot.delay == 0 && shot.shot_count < max_shots)
	{
		int	this_shot_index;
		Mix_PlayChannel(5, gun_shoot, 0);
		this_shot_index = create_shot(bullets, x, y);
		make_the_extra_popcorn_shots(bullets, this_shot_index);
		if (rage_now <= 0)
			shot.shot_count += 1 + more_shots_at_a_time;
		shot.delay = fire_rate;
		if (shot.shot_count >= max_shots)
			shot.reload = reload_speed;
		shot_happening = 1;
	}
}
