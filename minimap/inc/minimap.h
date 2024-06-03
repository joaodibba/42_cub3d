#ifndef MINIMAP_H
#define MINIMAP_H

#ifdef __APPLE__
	#include "../../mlx_macos/mlx.h"
#else
	#include "../../mlx_linux/mlx.h"
#endif

#include "../../libft/libft.h"
#include "../../core/model/inc/model.h"
#include "../../core/view/inc/view.h"
#include "../../core/controller/inc/controller.h"

void	render_2d_map(t_map *map, t_window *window);
void	draw_square(t_image *img, int x, int y, int size, int color);
#endif