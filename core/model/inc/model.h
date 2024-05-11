#ifndef __MODEL_H__
#define __MODEL_H__

#include "../../../mlx-linux/mlx.h"

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