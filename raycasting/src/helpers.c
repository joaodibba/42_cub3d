/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 01:50:46 by rphuyal           #+#    #+#             */
/*   Updated: 2024/06/01 18:07:56 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"

void    __rotate_vector(t_vec_double *vec, double angle) {

    double  old_x;

    old_x = vec->x;
    vec->x = vec->x * cos(angle) - vec->y * sin(angle);
    vec->y = old_x * sin(angle) + vec->y * cos(angle);
}

static void    __wall_distance(t_computes *computes) {

    if (computes->side == SIDE_X)
        computes->dist_to_wall = computes->side_dist.x - computes->delta.x;
    else
        computes->dist_to_wall = computes->side_dist.y - computes->delta.y;
}

void    __render_computes(t_computes *computes, int height) {
    // find the distance to the wall
    __wall_distance(computes);

    // calculate height of line to draw on screen
    computes->wall_height = (int)(height / computes->dist_to_wall);

    // calculate lowest and highest pixel to fill in current stripe
    computes->start_wall = -((computes->wall_height / 2) + (height / 2));
    if (computes->start_wall < 0)
        computes->start_wall = 0;

    computes->end_wall = (computes->wall_height / 2) + (height / 2);
    if (computes->end_wall >= height)
        computes->end_wall = height - 1;
}
