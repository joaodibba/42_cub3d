#ifndef CUB_H
# define CUB_H

// Platform-specific dependencies
# ifdef __APPLE__
#  include "../../mlx_macos/mlx.h"
# else
#  include "../../mlx_linux/mlx.h"
# endif

// Project-specific dependencies
# include "../../../libft/libft.h"
# include "../../../minimap/inc/minimap.h"
# include "../../controller/inc/controller.h"
# include "../../model/inc/model.h"
# include "../../parsing/inc/parser.h"
# include "../../view/inc/view.h"

// Standard libraries
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_cub
{
	t_window		*win;
	t_map			*map;
	t_controller	ctrl;
}					t_cub;

#endif