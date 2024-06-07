#ifndef MAIN_H
# define MAIN_H

// Standard libraries
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Platform-specific dependencies
#ifdef __APPLE__
    #include "../mlx_macos/mlx.h"
#else
    #include "../mlx_linux/mlx.h"
#endif

// Project-specific dependencies
#include "../libft/libft.h"

// include the components of the MVC architecture
# include "model.h"
# include "view.h"
# include "controller.h"

// include the additional components
# include "raycast.h"
# include "parser.h"


typedef struct s_cub
{
	t_window        *win;
	t_map           *map;
	t_player		player;
	t_controller    ctrl;
	t_computes	  	cols[WIN_WIDTH];
}   t_cub;



// minimap functions
void	render_2d_map(t_map *map, t_window *window);
void	draw_square(t_image *img, int x, int y, int size, int color);


// entities functions
void	init_player(t_player *player, t_map *map);

// players function
void	_player_start_pos(t_map *map, t_player *player);


#endif
