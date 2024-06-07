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
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
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
	player->plane = (t_vec_double){.x = player->dir.x, .y = player->dir.y};
	__rotate_vector(&player->plane, 90);
}

void	init_player(t_player *player, t_map *map)
{
	_player_start_pos(map, player);
	update_camera_plane(player);
}
