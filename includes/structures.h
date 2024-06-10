#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "settings.h"

// @brief The cordinates structure
typedef struct s_cordinates
{
	int				x;
	int				y;
}					t_cordinates;

// @brief The vector structure
typedef struct s_vec_double
{
	double			x;
	double			y;
}					t_vec_double;

// @brief The player structure
typedef struct s_player
{
	double			speed;
	t_vec_double	pos;
	t_vec_double	dir;
	t_vec_double	plane;
}					t_player;

// @brief The computes structure for raycasting
typedef struct s_computes {
    bool            hit;
    char            dir;
    int             side;
    int		        end_wall;
    int         	start_wall;
    int         	wall_height;
    double          dist_to_wall;
    double          wall_x;
    t_vec_double    hit_pos;
	t_vec_double	ray;
	t_cordinates    map;
    t_cordinates    step;
	t_vec_double	delta;
	t_vec_double	step_size;
} t_computes;

// @brief The controller structure for player movement and game state
typedef struct s_controller
{
	bool			mv_fw;
	bool			mv_bw;
	bool			mv_lf;
	bool			mv_rt;
	bool			rt_lf;
	bool			rt_rt;
	bool			game_over;
}					t_controller;

// @brief The image structure
typedef struct s_image
{
	void			*img;
	char			*addr;
	char			*path;
	int				bpp;
	int				line_len;
	int				width;
	int				height;
	int				endian;
}					t_image;

// @brief The window structure
typedef struct s_window
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	t_image			*img;
}					t_window;

// @brief The map structure
typedef struct s_map
{
	char			**map;
	unsigned int	floor;
	unsigned int	ceiling;
	t_image			*no;
	t_image			*so;
	t_image			*we;
	t_image			*ea;
}					t_map;

typedef struct s_cub
{
	t_window		*win;
	t_map			*map;
	t_controller	*ctrl;
	t_player		player;
	t_computes		cols[WIN_WIDTH];
}					t_cub;

#endif