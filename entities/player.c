/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:32:51 by rphuyal           #+#    #+#             */
/*   Updated: 2024/06/06 19:53:54 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

#define SQUARE_SIZE 50

void	build_player_2d_image(t_map *map, t_window *win)
{
	int	color;
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
				|| map->map[y][x] == 'E' || map->map[y][x] == 'W')
			{
				color = 0x000000FF;
				draw_square(win->img, x * SQUARE_SIZE, y * SQUARE_SIZE,
					SQUARE_SIZE, color);
			}
		}
	}
}

void	find_player_start(t_map *map, t_vec_double *cord)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
				|| map->map[y][x] == 'E' || map->map[y][x] == 'W')
			{
				printf("Player starting pos at: (%d, %d)\n", x, y);
				cord->x = (float)x;
				cord->y = (float)y;
				return ;
			}
			x++;
		}
		y++;
	}
	return ;
}

void	init_player(t_player *player, t_map *map)
{
	player->pos = (t_vec_double){.x = 0, .y = 0};
	player->dir = (t_vec_double){.x = 1, .y = 0};
	player->plane = (t_vec_double){.x = 0, .y = 0.66};
	find_player_start(map, &player->pos);
}
