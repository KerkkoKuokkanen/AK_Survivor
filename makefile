
NAME = AK_Survivor
SRCS =  srcs/main.c srcs/tools/keys.c srcs/tools/init.c srcs/player/anim.c srcs/player/move.c \
		srcs/tools/tools.c srcs/gun/gun.c srcs/enemy/enemy.c srcs/enemy/enem_anim.c \
		srcs/enemy/enem_move.c srcs/player/health.c srcs/orb.c srcs/particle.c \
		srcs/lvl/level_up.c srcs/lvl/upgrade.c srcs/enemy/push_back.c srcs/gun/bullets.c \
		srcs/gun/mag.c srcs/tools/time.c srcs/lvl/chooser.c srcs/gun/popcorn.c \
		srcs/gun/fractal.c srcs/enemy/spike_spawn.c srcs/enemy/make_enem.c \
		srcs/enemy/anim_choose.c srcs/gun/shock.c srcs/enemy/boss_spawn.c \
		srcs/tools/ysort.c srcs/egg/egg.c srcs/egg/arrow.c srcs/egg/egg_lvl.c \
		srcs/player/creep.c srcs/explosion/dead_whale.c srcs/dagger/dagger.c srcs/explosion/dark_aura.c \
		srcs/tools/write.c srcs/status/status.c srcs/tools/start_init.c srcs/enemy/hitbox.c \
		srcs/status/game_over.c srcs/tools/number.c srcs/status/menu.c srcs/status/audio.c \
		srcs/status/pause.c srcs/status/victory.c srcs/tools/aspect_ratio.c srcs/tools/controller.c

OBJ = $(SRCS:.c=.o)
HDR = -I ./srcs
FLAGS = 
CGFLAGS = 
INCLUDES	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Versions/A/Headers \
				-F./frameworks/
FRAMEWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				 \
				-framework SDL2 -framework SDL2_image \
				-framework SDL2_mixer

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(FLAGS) $(CGFLAGS) $(FRAMEWORKS) $(OBJ) -o $(NAME)

.c.o: $(HEADERS)
		@gcc $(FLAGS) $(INCLUDES) $(HDR) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean:
	@rm -rf $(OBJ)
	@rm -rf $(NAME);

re: fclean all