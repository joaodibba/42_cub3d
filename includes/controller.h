#ifndef CONTROLLER_H
# define CONTROLLER_H

# include <stdbool.h>
# include "model.h"

# ifdef __APPLE__
#  define ESC 53
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define UP 126
#  define DOWN 125
#  define LEFT 123
#  define RIGHT 124
# endif

# ifdef __linux__
#  define ESC 65307
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define UP 65362
#  define DOWN 65364
#  define LEFT 65361
#  define RIGHT 65363
# endif

// player macros
# define MOVE_SPEED 0.01
# define ROT_SPEED 0.555

typedef struct s_controller
{
	bool		mv_fw;
	bool		mv_bw;
	bool		mv_lf;
	bool		mv_rt;
	bool		rt_lf;
	bool		rt_rt;
	bool		game_over;
}				t_controller;

t_controller	init_controller(t_window *win);

#endif