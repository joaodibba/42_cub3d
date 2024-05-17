/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:37:39 by rphuyal           #+#    #+#             */
/*   Updated: 2024/05/17 01:02:36 by rphuyal          ###   ########.fr       */
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
    char    **map;
} t_info;

typedef struct s_player
{
    t_vec_double	pos;
    t_vec_double	dir;
    t_vec_double	plane;
} t_player;

typedef struct s_computes {
    int             side;
    bool            hit;
	t_vec_double	ray;
	t_cordinates    map;
    t_cordinates    step;
	t_vec_double	delta;
	t_vec_double	side_dist;
} t_computes;

// this is what the raycaster will modify
typedef struct s_pixel_col
{
    int				side;
    int				line_height;
    int				draw_start;
    int				draw_end;
} t_pixel_col;


// function defination
// TODO: change char **map to a t_map that contains char **map and int width and int height
void    raycast(t_info *info, t_player *player, int column);


#endif