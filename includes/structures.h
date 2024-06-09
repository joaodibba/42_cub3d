#ifndef STRUCTURES_H
# define STRUCTURES_H

#include "settings.h"

typedef enum e_move_dir
{
    TOLEFT,
    TORIGHT,
    FORWARD,
    BACKWARD
} t_move_dir;

typedef struct s_cordinates
{
    int	x;
    int	y;
} t_cordinates;

typedef struct s_vec_double
{
    double	x;
    double	y;
} t_vec_double;

typedef struct s_player
{
    double			fov;
    double			speed;
    t_vec_double	pos;
    t_vec_double	dir;
    t_vec_double	plane;
} t_player;


// this is what the raycaster will modify
typedef struct s_computes {
    bool            hit;
    char            dir;
    int             side;
    int             end_wall;
    int             start_wall;
    int             wall_height;
    double          dist_to_wall;
	t_vec_double	ray;
	t_cordinates    map;
    t_cordinates    step;
	t_vec_double	delta;
	t_vec_double	side_dist;
} t_computes;


typedef struct s_controller
{
	bool		mv_fw;
	bool		mv_bw;
	bool		mv_lf;
	bool		mv_rt;
	bool		rt_lf;
	bool		rt_rt;
	bool		game_over;
}				t_controller;


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

typedef struct s_cub
{
	t_window		*win;
	t_map			*map;
	t_controller	*ctrl;
	t_player		player;
	t_computes		cols[WIN_WIDTH];
}					t_cub;

#endif