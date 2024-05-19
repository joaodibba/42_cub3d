/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:37:39 by rphuyal           #+#    #+#             */
/*   Updated: 2024/05/20 00:41:49 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RAYCASTER_H__
# define __RAYCASTER_H__

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

// constants
# define WINDOW_W 6
# define WINDOW_H 6

# define SIDE_X 0
# define SIDE_Y 1

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

typedef struct s_info
{
    int     width;
    int     height;
    int     **map;
} t_info;

typedef struct s_player
{
    t_vec_double	pos;
    t_vec_double	dir;
    t_vec_double	plane;
} t_player;

// this is what the raycaster will modify
typedef struct s_computes {
    bool            hit;
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


// function defination
void    raycast(int column, t_info *info, t_player *player);
void    __render_computes(t_computes *computes, int height);

// loggers
void __log_computes(t_computes *computes);
void __log_results(t_computes *computes);


#endif