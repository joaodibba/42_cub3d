#ifndef __CUB_H__
# define __CUB_H__

// Dependencies
#if defined(__APPLE__)
	#include "../../mlx_macos/mlx.h"
#else
	#include "../../mlx_linux/mlx.h"
#endif

#include "../../../libft/libft.h"


#include "../../model/inc/model.h"
#include "../../view/inc/view.h"
#include "../../controller/inc/controller.h"


// Standard libraries
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#endif