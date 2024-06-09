/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:43:44 by rphuyal           #+#    #+#             */
/*   Updated: 2024/06/09 16:30:49 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

// loggers
void		__log_results(t_computes *computes);
void		__log_computes(t_computes *computes);
// more computation functions
void		__render_computes(t_computes *computes, t_player *player);

static void	__dda(t_computes *computes, char **map)
{
	computes->hit = false;
	while (true)
	{
		// jump to the nearest side
		if (computes->step_size.x < computes->step_size.y)
		{
			computes->step_size.x += computes->delta.x;
			computes->map.x += computes->step.x;
			computes->side = SIDE_X;
		}
		else
		{
			computes->step_size.y += computes->delta.y;
			computes->map.y += computes->step.y;
			computes->side = SIDE_Y;
		}
		if (computes->map.x < 0 || computes->map.y < 0)
			break ;
		if (map[computes->map.x] && map[computes->map.x][computes->map.y] == '1')
		{
			computes->hit = true;
			break ;
		}
	}
}

static void	__sides(t_computes *computes, t_player *player)
{
	if (computes->ray.x < 0)
	{
		computes->step.x = -1;
		computes->step_size.x = (player->pos.x - computes->map.x)
			* computes->delta.x;
	}
	else
	{
		computes->step.x = 1;
		computes->step_size.x = ((computes->map.x + 1.0) - player->pos.x)
			* computes->delta.x;
	}
	if (computes->ray.y < 0)
	{
		computes->step.y = -1;
		computes->step_size.y = (player->pos.y - computes->map.y)
			* computes->delta.y;
	}
	else
	{
		computes->step.y = 1;
		computes->step_size.y = ((computes->map.y + 1.0) - player->pos.y)
			* computes->delta.y;
	}
}

static void	__deltas(t_computes *computes)
{
	// compute the deltas for the ray
	computes->delta.x = fabs(1 / computes->ray.x);
	computes->delta.y = fabs(1 / computes->ray.y);
}

static void	__helper_vecs(t_computes *computes, t_player *player, double camera)
{
	// ray starts at the player's position, not the camera
	// so we need to get the player's position in the map, which is a square
	computes->map.x = (int)player->pos.x;
	computes->map.y = (int)player->pos.y;
	// get the camera plane ops straight from the eye of the player
	computes->ray.x = player->dir.x + (player->plane.x * camera);
	computes->ray.y = player->dir.y + (player->plane.y * camera);
}

void	raycast(int column, t_map *map, t_player *player, t_computes *computes)
{
	double camera;

	// get where the in the x-cordinate the camera plane is
	camera = ((2 * column / (double)WIN_WIDTH) - 1);
	__helper_vecs(computes, player, camera);
	__deltas(computes);
	__sides(computes, player);
	// __log_computes(computes);
	__dda(computes, map->map);
	__render_computes(computes, player);
	// __log_results(computes);
	return ;
}