
#include "../top_down.h"

// functions to call:
// time main
// boss_spwan
// creep main with all == NULL
// orb_main
// egg_main
// bullet main with everything as NULL what can be
// particle main
// shock_the_enemies
// dead_whale
// dagger_main
// health main
// lvl_up
void	pre_game(t_enemy *enem)
{
	if (enem != NULL)
		bzero(enem, sizeof(t_enemy) * E_COUNT);
	init_global();
	time_main(0, NULL, NULL, NULL, START_INIT);
	boss_spawner(NULL, NULL, NULL, START_INIT, 0);
	creep_main(NULL, NULL, NULL);
	orb_main(NULL, NULL, NULL, NULL, START_INIT);
	egg_main(NULL, NULL, START_INIT);
	bullets_main(0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	particle_main(NULL, NULL, NULL, START_INIT);
	shock_the_enemies(NULL, NULL, NULL, 0, START_INIT);
	dark_aura_main(NULL, NULL, NULL, NULL);
	dead_whale_explosion_main(NULL, 0, NULL, START_INIT, NULL, NULL);
	dagger_main(NULL, START_INIT, NULL, NULL, NULL);
	health_main(NULL, NULL, NULL, START_INIT);
	level_up_main(NULL, 0, NULL, NULL, NULL, NULL, NULL, START_INIT);
}
