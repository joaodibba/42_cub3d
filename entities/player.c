#include "../includes/main.h"

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
	printf("Found player (%c) at: (%d, %d)\n", map->map[y][x], x, y);
	player->pos.x = 0.5 + (float)x;
	player->pos.y = 0.5 + (float)y;
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
			if (__player_exists_here(map, player, y, x))
				return ;
			y++;
		}
		x++;
	}
	return;
}

void	update_camera_plane(t_player *player)
{
	player->plane = (t_vec_double){.x = player->dir.x, .y = player->dir.y};
	rotate_vector(&player->plane, 90);
	player->plane.x = player->plane.x * (player->fov / 100);
	player->plane.y = player->plane.y * (player->fov / 100);
}

void	init_player(t_player *player, t_map *map)
{
	player->fov = 100;
	_player_start_pos(map, player);
	update_camera_plane(player);
}
