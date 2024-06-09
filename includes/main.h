#ifndef MAIN_H
# define MAIN_H

// Standard libraries
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>


// Platform-specific dependencies
# ifdef __APPLE__
#  include "../mlx_macos/mlx.h"
# else
#  include "../mlx_linux/mlx.h"
# endif

// Project-specific dependencies
# include "../libft/libft.h"

# include "structures.h"
# include "settings.h"

// Macros for the raycaster
# define SIDE_X 0
# define SIDE_Y 1
# define WALLSCALE 10
# define TEXTURE_SIZE 128


bool			parser(char *path, t_window **win, t_map **map);

t_controller	*init_controller(t_window *win);
void			render_2d_map(t_map *map, t_window *win, t_player player);
void			draw_square(t_image *img, int x, int y, int size,
						int color);

// entities functions
void			init_player(t_player *player, t_map *map);

// players function
void    		create_wall(t_image *image, t_computes *computes, t_map *map, t_player *player);
void				_player_start_pos(t_map *map, t_player *player);

void			raycast(int column, t_map *map, t_player *player, t_computes *computes);
void			__render_computes(t_computes *computes, t_player *player);

// helper functions
void    		__rotate_vector(t_vec_double *vec, double angle);

// loggers
void    		__log_computes(t_computes *computes);
void    		__log_results(t_computes *computes);

// function definations
void			put_pixel(t_image *img, int x, int y, int color);
void			draw_square(t_image *img, int x, int y, int size, int color);
void			draw_line(t_image *img, t_vec_double start, t_vec_double end, int color);

#endif
