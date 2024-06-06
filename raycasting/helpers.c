/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 01:50:46 by rphuyal           #+#    #+#             */
/*   Updated: 2024/06/06 22:27:01 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	__rotate_vector(t_vec_double *vec, double angle)
{
    angle = angle * (M_PI / 180);
	vec->y = vec->x * sin(angle) + vec->y * cos(angle);
	vec->x = vec->x * cos(angle) - vec->y * sin(angle);
}

static void	__wall_infos(t_computes *computes)
{
	if (computes->side == SIDE_X)
		computes->dist_to_wall = computes->side_dist.x - computes->delta.x;
	else
		computes->dist_to_wall = computes->side_dist.y - computes->delta.y;
}

/* calculate which side the hit is -> "NEWS" */
static void	__hit_infos(t_computes *computes)
{
	if (computes->side == SIDE_X)
	{
		if (computes->ray.x > 0)
			computes->dir = 'E';
		else
			computes->dir = 'W';
	}
	else
	{
		if (computes->ray.y > 0)
			computes->dir = 'S';
		else
			computes->dir = 'N';
	}
}

void	__render_computes(t_computes *computes, size_t height)
{
	// find the distance to the wall
	__wall_infos(computes);
	// find the hit infos
	__hit_infos(computes);
	// calculate height of line to draw on screen
	computes->wall_height = (int)((double)height / computes->dist_to_wall);
	// calculate lowest and highest pixel to fill in current stripe
	computes->start_wall = -((computes->wall_height / 2) + (height / 2));
	if (computes->start_wall < 0)
		computes->start_wall = 0;
	computes->end_wall = (computes->wall_height / 2) + (height / 2);
	if (computes->end_wall >= height)
		computes->end_wall = height - 1;
}
