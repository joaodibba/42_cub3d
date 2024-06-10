#ifndef MAIN_H
# define MAIN_H

// ------------------ Dependencies ------------------
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>

// ------------------ Local Headers ------------------

# ifdef __APPLE__
#  include "../mlx_macos/mlx.h"
# else
#  include "../mlx_linux/mlx.h"
# endif

# include "../libft/libft.h"
# include "structures.h"
# include "settings.h"

// ------------------ Macros ------------------
# define SIDE_X 0
# define SIDE_Y 1
# define WALLSCALE 10
# define TEXTURE_SIZE 128
# define WALL_SCALER 0.6

# ifdef __APPLE__
#  define ESC 53
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define Q 12
#  define E 14
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
#  define Q 113
#  define E 101
#  define UP 65362
#  define DOWN 65364
#  define LEFT 65361
#  define RIGHT 65363
# endif

// ------------------ Functions ------------------

bool	parser(t_cub *cub, char *path, t_window *win, t_map *map);

int		exit_cub(t_cub *cub);
void	free_cub(t_cub *cub);
bool	initialization(t_cub *cub);

t_controller	*init_controller(t_cub *cub);
void			init_player(t_player *player, t_map *map);
void			player_move(t_player *player, t_controller *controller, char **map);

// ------------------ Rendering ------------------

void			paint_window(t_window *win, int ceiling_color, int floor_color);
void			render_2d_map(t_cub *cub, t_map *map, t_window *win, t_player player);
void			draw_square(t_image *img, int x, int y, int size, int color);
void			put_pixel(t_image *img, int x, int y, int color);
void			render_dimension_3d(t_cub *cub);

// ------------------ Raycasting ------------------

void			raycast(int column, t_map *map, t_player *player, t_computes *computes);

#endif
