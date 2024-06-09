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
	player->pos = (t_vec_double){.x = (float)x + 0.5, .y = (float)y + 0.5};
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
