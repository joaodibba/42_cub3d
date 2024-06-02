#ifndef __CONTROLLER_H__
# define __CONTROLLER_H__

#include <stdbool.h>
#include "../../../libft/libft.h"

#ifndef WIN_WIDTH
	# define WIN_WIDTH 800
#endif

#ifndef WIN_HEIGHT
	# define WIN_HEIGHT 600
#endif


# ifdef __APPLE__
	# define ESC 53
	# define W 13
	# define A 0
	# define S 1
	# define D 2
	# define UP 126
	# define DOWN 125
	# define LEFT 123
	# define RIGHT 124
#endif

# ifdef __linux__
	# define ESC 65307
	# define W 119
	# define A 97
	# define S 115
	# define D 100
	# define UP 65362
	# define DOWN 65364
	# define LEFT 65361
	# define RIGHT 65363
#endif

typedef struct s_controller
{
	bool    mv_fw;
	bool    mv_bw;
	bool    mv_lf;
	bool    mv_rt;
	bool    rt_lf;
	bool    rt_rt;
	bool    game_over;
}           t_controller;

int	mouse_move(int x, int y, t_controller *ctrl);
int	key_release(int key, t_controller *ctrl);
int	key_press(int key, t_controller *ctrl);

#endif