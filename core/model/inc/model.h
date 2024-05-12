#ifndef __MODEL_H__
#define __MODEL_H__

#if defined(__APPLE__)
	#include "../../mlx_macos/mlx.h"
#else
	#include "../../mlx_linux/mlx.h"
#endif

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

// window data
typedef struct s_window
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_img	img;
}	t_window;


# endif