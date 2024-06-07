#ifndef MINIMAP_H
# define MINIMAP_H

# ifdef __APPLE__
#  include "../../mlx_macos/mlx.h"
# else
#  include "../../mlx_linux/mlx.h"
# endif

# include "../../core/controller/inc/controller.h"
# include "../../core/model/inc/model.h"
# include "../../core/view/inc/view.h"
# include "../../core/parsing/inc/parser.h"
# include "../../libft/libft.h"

# ifndef SQUARE_SIZE
#  define SQUARE_SIZE 10
# endif

void	render_2d_map(t_map *map, t_window *window);
void	put_pixel(t_image *img, int x, int y, int color);
#endif