#ifndef __RAYCASTER_H__
# define __RAYCASTER_H__

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

# define PI 3.1415926535 // maxium precision (painful)

typedef struct s_vec_double
{
    double x;
    double y;
} t_vec_double;

typedef struct s_vec_int
{
    int x;
    int y;
} t_vec_int;

typedef struct s_player
{
    t_vec_double pos;
    t_vec_double dir;
    t_vec_double plane;
} t_player;

#endif