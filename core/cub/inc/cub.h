#ifndef __CUB_H__
# define __CUB_H__

#if defined(__APPLE__)
	#include "../../mlx_macos/mlx.h"
#else
	#include "../../mlx_linux/mlx.h"
#endif

#include "../../model/inc/model.h"
#include "../../controller/inc/controller.h"
#include "../../../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#endif