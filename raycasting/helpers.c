/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 01:50:46 by rphuyal           #+#    #+#             */
/*   Updated: 2024/06/10 05:26:48 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

/* calculate the distance to the wall based on the side hit */
static void	__wall_info(t_computes *computes, t_player *player)
{
	if (computes->side == SIDE_X)
		computes->dist_to_wall = (computes->map.x - player->pos.x + (1
					- computes->step.x) / 2) / computes->ray.x;
	else
		computes->dist_to_wall = (computes->map.y - player->pos.y + (1
					- computes->step.y) / 2) / computes->ray.y;
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

/* these computed variables are used in the 3D rendering */
void	__render_computes(t_computes *computes, t_player *player)
{
	__wall_info(computes, player);
	__hit_infos(computes);
	computes->wall_height = (int)((double)WIN_HEIGHT / computes->dist_to_wall)
		*WALL_SCALER;
	computes->start_wall = fmax(0, (WIN_HEIGHT / 2) - (computes->wall_height
				/ 2));
	computes->end_wall = fmin(WIN_HEIGHT, (WIN_HEIGHT / 2)
			+ (int)(computes->wall_height / 2));
	computes->hit_pos.x = player->pos.x + computes->dist_to_wall
		* computes->ray.x;
	computes->hit_pos.y = player->pos.y + computes->dist_to_wall
		* computes->ray.y;
	if (computes->dir == 'N' || computes->dir == 'S')
		computes->wall_x = computes->hit_pos.x - floor(computes->hit_pos.x);
	else
		computes->wall_x = computes->hit_pos.y - floor(computes->hit_pos.y);
}
