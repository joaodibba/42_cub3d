#ifndef MODEL_H
# define MODEL_H

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
}			t_image;

// @brief The window structure
typedef struct s_window
{
	void *mlx;    // mlx identifier
	void *win;    // window identifier
	int width;    // window width
	int height;   // window height
	t_image *img; // image data
}			t_window;

// @brief The map structure
typedef struct s_map
{
	char	**map;
	unsigned int	floor; // floor color
	unsigned int	ceiling; // ceiling color
	t_image	*no;
	t_image	*so;
	t_image	*we;
	t_image	*ea;
}			t_map;


# endif
