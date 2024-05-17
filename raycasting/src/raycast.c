/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:43:44 by rphuyal           #+#    #+#             */
/*   Updated: 2024/05/17 11:09:32 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"

static void __dda(t_computes *computes, int **map) {

	computes->hit = false;
	while (true) {
		// jump to the nearest side
		if (computes->side_dist.x < computes->side_dist.y) {
			computes->side_dist.x += computes->delta.x;
			computes->map.x += computes->step.x;
			computes->side = SIDE_X;
		}
		else {
			computes->side_dist.y += computes->delta.y;
			computes->map.y += computes->step.y;
			computes->side = SIDE_Y;
		}

		if (map[computes->map.x][computes->map.y] > 0) {
			computes->hit = true;
			break ;
		}
	}
}

static void	__sides(t_computes *computes, t_player *player) {
	if (computes->ray.x < 0) {
		computes->step.x = -1;
		computes->side_dist.x = (player->pos.x - computes->map.x) * computes->delta.x;
	}
	else {
		computes->step.x = 1;
		computes->side_dist.x = ((computes->map.x + 1.0) - player->pos.x) * computes->delta.x;
	}
	if (computes->ray.y < 0) {
		computes->step.y = -1;
		computes->side_dist.y = (player->pos.y - computes->map.y) * computes->delta.y;
	}
	else {
		computes->step.y = 1;
		computes->side_dist.y = ((computes->map.y + 1.0) - player->pos.y) * computes->delta.y;
	}
}

static void	__deltas(t_computes *computes) {
	int	guard_x;
	int	guard_y;

	// used for shortcurcit
	guard_x = computes->ray.x > 0;
	guard_y = computes->ray.y > 0;

	// compute the deltas if the ray is pos, else a positive value
	computes->delta.x = (guard_x * fabs(1 / computes->ray.x)) + (!guard_x * 1e30);
	computes->delta.y = (guard_y * fabs(1 / computes->ray.y)) + (!guard_y * 1e30);
}

static void	__pos_dir(t_computes *computes, t_player *player, double camera) {

	// ray starts at the player's position, not the camera
	// so we need to get the player's position in the map, which is a square
	computes->map.x = (int)player->pos.x;
	computes->map.y = (int)player->pos.y;

	// get the camera plane ops straight from the eye of the player
	computes->ray.x = player->dir.x + (player->plane.x * camera);
	computes->ray.y = player->dir.y + (player->plane.y * camera);
}

void	raycast(int column, t_info *info, t_player *player) {

	double		camera;
	t_computes	computes;

	// get where the in the x-cordinate the camera plane is
	camera = (2 * (column / (double)info->width)) - 1;
	__pos_dir(&computes, player, camera);
	__deltas(&computes);
	__sides(&computes, player);
	__log_computes(&computes);
	__dda(&computes, info->map);
	__log_results(&computes);
	return ;
}