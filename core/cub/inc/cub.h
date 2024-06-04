#ifndef CUB_H
# define CUB_H

// Platform-specific dependencies
#ifdef __APPLE__
    #include "../../mlx_macos/mlx.h"
#else
    #include "../../mlx_linux/mlx.h"
#endif


// Project-specific dependencies
#include "../../../libft/libft.h"
#include "../../model/inc/model.h"
#include "../../view/inc/view.h"
#include "../../controller/inc/controller.h"
#include "../../../minimap/inc/minimap.h"
#include "../../parsing/inc/parser.h"

// Standard libraries
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct s_cub
{
	t_window        *win;
	t_map           *map;
	t_controller    ctrl;
}   t_cub;


#endif // CUB_H
