#ifndef MODEL_H
#define MODEL_H

#include <stdint.h>

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
	size_t	width;
	size_t	height;
	t_color	*floor;
	t_color	*ceiling;
	t_image	*no;
	t_image	*so;
	t_image	*we;
	t_image	*ea;
}	t_map;


# endif