
#include "../top_down.h"
#define WEAK 8

void	make_zombie(t_enemy *enem, t_text_enemy text)
{
	enem->type = 1;
	enem->text.text.text = text.zomb.text.text;
	enem->text.rect.w = text.zomb.rect.w;
	enem->text.rect.h = text.zomb.rect.h;
	enem->hit_text.text = text.zomb_hit_text.text;
	enem->frame.y = 0;
	enem->frame.w = 64;
	enem->frame.h = 64;
	enem->hbox.w = 30;
	enem->hbox.h = 64;
	enem->hbox.x = 0;
	enem->hbox.y = 20;
	enem->push_back_amount = 3;
	enem->on_screen = 0;
	enem->got_hit = 0;
	enem->hp = 80;
	enem->enem_speed = 4;
	enem->got_shot = 0;
	enem->push.duration = 0;
	enem->frc = 0;
}

void	make_red_enemy(t_enemy *enem, t_text_enemy text)
{
	enem->type = 2;
	enem->text.text.text = text.red_enemy.text.text;
	enem->text.rect.w = text.red_enemy.rect.w;
	enem->text.rect.h = text.red_enemy.rect.h;
	enem->hit_text.text = text.red_enemy_hit.text;
	enem->frame.y = 0;
	enem->frame.w = 32;
	enem->frame.h = 32;
	enem->hbox.w = 30;
	enem->hbox.h = 64;
	enem->hbox.x = 0;
	enem->hbox.y = 20;
	enem->push_back_amount = 2;
	enem->on_screen = 0;
	enem->got_hit = 0;
	enem->hp = 480;
	enem->enem_speed = 4;
	enem->got_shot = 0;
	enem->push.duration = 0;
	enem->frc = 0;
}

void	make_annoying_enemy(t_enemy *enem, t_text_enemy text)
{
	enem->type = 3;
	enem->text.text.text = text.annoying_enemy.text.text;
	enem->text.rect.w = text.annoying_enemy.rect.w;
	enem->text.rect.h = text.annoying_enemy.rect.h;
	enem->hit_text.text = text.annoying_hit.text;
	enem->frame.y = 0;
	enem->frame.w = 16;
	enem->frame.h = 32;
	enem->hbox.w = 32;
	enem->hbox.h = 64;
	enem->hbox.x = 0;
	enem->hbox.y = 20;
	enem->push_back_amount = 5;
	enem->on_screen = 0;
	enem->got_hit = 0;
	if (all_seconds < 180)
		enem->hp = (all_seconds / 1.2 + 1) * 16;
	else
		enem->hp = (all_seconds * 1.6) * 16;
	enem->enem_speed = 1;
	enem->got_shot = 0;
	enem->push.duration = 0;
	enem->frc = 0;
}

void	make_boss(t_enemy *enem, t_text_enemy text, int hp, int lifetime)
{
	enem->type = 4;
	enem->text.text.text = text.boss.text.text;
	enem->text.rect.w = text.boss.rect.w;
	enem->text.rect.h = text.boss.rect.h;
	enem->hit_text.text = text.boss_hit.text;
	enem->frame.w = 192;
	enem->frame.h = 180;
	enem->frame.y = 0;
	enem->hbox.w = 140;
	enem->hbox.h = 130;
	enem->push_back_amount = 0;
	enem->on_screen = 0;
	enem->got_hit = 0;
	enem->hp = hp;
	enem->enem_speed = 3;
	enem->got_shot = 0;
	enem->push.duration = 0;
	enem->frc = 0;
	enem->life_time = lifetime;
}

void	make_brown_enem(t_enemy *enem, t_text_enemy text)
{
	enem->type = 5;
	enem->text.text.text = text.brown_enem.text.text;
	enem->text.rect.w = text.brown_enem.rect.w;
	enem->text.rect.h = text.brown_enem.rect.h;
	enem->hit_text.text = text.brown_enem_hit.text;
	enem->frame.y = 0;
	enem->frame.w = 40;
	enem->frame.h = 40;
	enem->hbox.w = 40;
	enem->hbox.h = 80;
	enem->hbox.x = 0;
	enem->hbox.y = 100;
	enem->push_back_amount = 2;
	enem->on_screen = 0;
	enem->got_hit = 0;
	enem->hp = 1080;
	enem->enem_speed = 4;
	enem->got_shot = 0;
	enem->push.duration = 0;
	enem->frc = 0;
}

void	make_crab_enemy(t_enemy *enem, t_text_enemy text)
{
	enem->type = 6;
	enem->text.text.text = text.crab.text.text;
	enem->text.rect.w = text.crab.rect.w;
	enem->text.rect.h = text.crab.rect.h;
	enem->hit_text.text = text.crab_hit.text;
	enem->frame.y = 0;
	enem->frame.w = 200;
	enem->frame.h = 80;
	enem->hbox.w = 60;
	enem->hbox.h = 60;
	enem->push_back_amount = 2;
	enem->on_screen = 0;
	enem->got_hit = 0;
	enem->hp = 1780;
	enem->enem_speed = 4;
	enem->got_shot = 0;
	enem->push.duration = 0;
	enem->frc = 0;
}

void	make_minotaur_enemy(t_enemy *enem, t_text_enemy text)
{
	enem->type = 7;
	enem->text.text.text = text.minotaur.text.text;
	enem->text.rect.w = text.minotaur.rect.w;
	enem->text.rect.h = text.minotaur.rect.h;
	enem->hit_text.text = text.minotaur_hit.text;
	enem->frame.y = 0;
	enem->frame.w = 180;
	enem->frame.h = 150;
	enem->hbox.w = 30;
	enem->hbox.h = 80;
	enem->push_back_amount = 2;
	enem->on_screen = 0;
	enem->got_hit = 0;
	enem->hp = 3840;
	enem->enem_speed = 4;
	enem->got_shot = 0;
	enem->push.duration = 0;
	enem->frc = 0;
}

void	make_red_frog_enemy(t_enemy *enem, t_text_enemy text)
{
	enem->type = 8;
	enem->text.text.text = text.red_frog.text.text;
	enem->text.rect.w = text.red_frog.rect.w;
	enem->text.rect.h = text.red_frog.rect.h;
	enem->hit_text.text = text.red_frog_hit.text;
	enem->frame.y = 0;
	enem->frame.w = 190;
	enem->frame.h = 185;
	enem->hbox.w = 70;
	enem->hbox.h = 80;
	enem->push_back_amount = 2;
	enem->on_screen = 0;
	enem->got_hit = 0;
	enem->hp = 7100;
	enem->enem_speed = 3;
	enem->got_shot = 0;
	enem->push.duration = 0;
	enem->frc = 0;
}

void	make_scorpion_enemy(t_enemy *enem, t_text_enemy text)
{
	enem->type = 9;
	enem->text.text.text = text.scorpion.text.text;
	enem->text.rect.w = text.scorpion.rect.w;
	enem->text.rect.h = text.scorpion.rect.h;
	enem->hit_text.text = text.scorpion_hit.text;
	enem->frame.y = 0;
	enem->frame.w = 190;
	enem->frame.h = 155;
	enem->hbox.w = 65;
	enem->hbox.h = 65;
	enem->push_back_amount = 2;
	enem->on_screen = 0;
	enem->got_hit = 0;
	enem->hp = 14550;
	enem->enem_speed = 3;
	enem->got_shot = 0;
	enem->push.duration = 0;
	enem->frc = 0;
}

int	get_chooser(int sign)
{
	int	rand_annoying = rand() % 35;

	if (sign == 0 && rand_annoying == 3)
		return (7);
	if (all_seconds < 63)
		return (0);
	if (all_seconds < 93)
		return (rand() % 2);
	if (all_seconds >= 93 && all_seconds < 125)
		return (1);
	if (all_seconds >= 125 && all_seconds < 170)
		return ((rand() % 2) + 1);
	if (all_seconds >= 170 && all_seconds < 190)
		return (2);
	if (all_seconds >= 190 && all_seconds < 240)
		return ((rand() % 2) + 2);
	if (all_seconds >= 240 && all_seconds < 285)
		return (3);
	if (all_seconds >= 285 && all_seconds < 320)
		return ((rand() % 2) + 3);
	if (all_seconds >= 320 && all_seconds < 360)
		return (4);
	if (all_seconds >= 360 && all_seconds < 450)
		return ((rand() % 2) + 4);
	if (all_seconds >= 450 && all_seconds < 520)
		return ((rand() % 3) + 4);
	if (all_seconds >= 520 && all_seconds < 560)
		return ((rand() % 2) + 5);
	return (6);
}

void	choose_enemy(t_enemy *enem, t_text_enemy text, int sign)
{
	int		chooser = get_chooser(sign);
	void	(*make_func[8])(t_enemy *enem, t_text_enemy text) = {make_zombie, make_red_enemy, make_brown_enem, make_crab_enemy, make_minotaur_enemy, make_red_frog_enemy, make_scorpion_enemy, make_annoying_enemy};

	(make_func[chooser])(enem, text);
}

int	weak_enem_spawn(t_enemy *enem, t_text_enemy text, int current)
{
	if (all_seconds < 90)
		return (0);
	int		type;
	void	(*make_func[7])(t_enemy *enem, t_text_enemy text) = {make_zombie, make_red_enemy, make_brown_enem, make_crab_enemy, make_minotaur_enemy, make_red_frog_enemy, make_scorpion_enemy};
	if (all_seconds > 550)
		type = get_chooser(1);
	else if (all_seconds > 420)
		type = get_chooser(1) - 1;
	else
		type = get_chooser(1) - 2;
	if (type < 0)
		type = 0;
	(make_func[rand() % (type + 1)])(&enem[current], text);
	check_the_space_to_spawn(enem, current);
	return (1);
}
