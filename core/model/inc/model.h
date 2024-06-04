#ifndef MODEL_H
#define MODEL_H

#ifdef __APPLE__
	#include "../../mlx_macos/mlx.h"
#else
	#include "../../mlx_linux/mlx.h"
	#include "stdint.h"
#endif


#ifndef WIN_WIDTH
	# define WIN_WIDTH 800
#endif

#ifndef WIN_HEIGHT
	# define WIN_HEIGHT 600
#endif

// @brief The image structure
typedef struct s_image {
	void	*img; // image identifier
	char	*addr; // address where the image is stored in memory
	char	*path; // path to the image file
	int		bpp; // bits per pixel
	int		line_len; // size of a line in bytes
	int		width; 
	int		height;
	int		endian;
}	t_image;

// @brief The window structure
typedef struct s_window
{
	void	*mlx; // mlx identifier
	void	*win; // window identifier
	int		width; // window width
	int		height; // window height
	t_image	*img; // image data
}	t_window;

// @brief The color structure
typedef struct s_color
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
}	t_color;

// @brief The map structure
typedef struct s_map
{
	char	**map;
	t_color	*floor;
	t_color	*ceiling;
	t_image	*no;
	t_image	*so;
	t_image	*we;
	t_image	*ea;
}	t_map;


# endif
