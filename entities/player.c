/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:50:12 by rphuyal           #+#    #+#             */
/*   Updated: 2024/06/10 21:50:13 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	rotate_vector(t_vec_double *vec, double angle);

void	__display_player_info(t_player *player, char dir)
{
	printf("------------------------------\n");
	printf(GREEN BOLD "Player: \n" RESET_COLOR);
	printf(CYAN "Found at: (%d, %d)\n" RESET_COLOR, (int)player->pos.x, \
		(int)player->pos.y);
	printf(CYAN "Direction: (%c)\n" RESET_COLOR, dir);
}

bool	__player_exists_here(t_map *map, t_player *player, unsigned int x,
		unsigned int y)
{
	if (map->map[y][x] == 'N')
		player->dir = (t_vec_double){.x = 0, .y = -1};
	else if (map->map[y][x] == 'S')
		player->dir = (t_vec_double){.x = 0, .y = 1};
	else if (map->map[y][x] == 'E')
		player->dir = (t_vec_double){.x = 1, .y = 0};
	else if (map->map[y][x] == 'W')
		player->dir = (t_vec_double){.x = -1, .y = 0};
	else
		return (false);
	player->pos = (t_vec_double){.x = (double)x + 0.5, .y = (double)y + 0.5};
	__display_player_info(player, map->map[y][x]);
	map->map[y][x] = '0';
	return (true);
}

void	_player_start_pos(t_map *map, t_player *player)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (map->map && map->map[y])
	{
		x = 0;
		while (map->map[y] && map->map[y][x])
		{
			if (__player_exists_here(map, player, x, y))
				return ;
			x++;
		}
		y++;
	}
	return ;
}

void	update_camera_plane(t_player *player)
{
	t_vec_double	plane;

	plane = (t_vec_double){.x = player->dir.x, .y = player->dir.y};
	rotate_vector(&plane, 90);
	player->plane.x = plane.x;
	player->plane.y = plane.y;
}

void	init_player(t_player *player, t_map *map)
{
	_player_start_pos(map, player);
	update_camera_plane(player);
}
