#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <math.h>

// include stuffs from the model
# include "model.h"
# include <stdbool.h>
# include <stddef.h>

# define SIDE_X 0
# define SIDE_Y 1

# define WALLSCALE 10

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
    t_vec_double    hit_pos;
	t_vec_double	ray;
	t_cordinates    map;
    t_cordinates    step;
	t_vec_double	delta;
	t_vec_double	side_dist;
} t_computes;


// function definations
void	raycast(int column, t_map *map, t_player *player, t_computes *computes);

// helper functions
void    rotate_vector(t_vec_double *vec, double angle);


#endif