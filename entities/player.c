#include "../includes/main.h"

bool	__player_exists_here(t_map *map, t_player *player, unsigned int x,
		unsigned int y)
{
	if (map->map[x][y] == 'N')
		player->dir = (t_vec_double){.x = 0, .y = -1};
	else if (map->map[x][y] == 'S')
		player->dir = (t_vec_double){.x = 0, .y = 1};
	else if (map->map[x][y] == 'E')
		player->dir = (t_vec_double){.x = 1, .y = 0};
	else if (map->map[x][y] == 'W')
		player->dir = (t_vec_double){.x = -1, .y = 0};
	else
		return (false);
	// printf("Found player (%c) at: (%d, %d)\n", map->map[x][y], x, y);
	player->pos.x = 0.5 + (float)x;
	player->pos.y = 0.5 + (float)y;
	map->map[x][y] = '0';
	return (true);
}

void	_player_start_pos(t_map *map, t_player *player)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	while (map->map && map->map[x])
	{
		y = 0;
		while (map->map[x] && map->map[x][y])
		{
			if (__player_exists_here(map, player, x, y))
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
	__rotate_vector(&player->plane, player->fov);
	player->plane.x *= tan(player->fov / 2 * (M_PI / 180));
	player->plane.y *= tan(player->fov / 2 * (M_PI / 180));
}

void	init_player(t_player *player, t_map *map)
{
	player->fov = 90;
	_player_start_pos(map, player);
	update_camera_plane(player);

	printf("Player dir: (%f, %f)\n", player->dir.x, player->dir.y);
	printf("Player pos: (%f, %f)\n", player->pos.x, player->pos.y);
}
