#include "../includes/main.h"
#define SQUARE_SIZE 50

void build_player_2d_image(t_map *map, t_window *win) {
	int	x;
	int	y;
	int	color;

	for (y = 0; y < map->height; y++)
	{
		for (x = 0; x < map->width; x++)
		{
            if (map->map[y][x] == 'N' \
                || map->map[y][x] == 'S' \
                || map->map[y][x] == 'E' \
                || map->map[y][x] == 'W')
            {
                color = 0x000000FF;
                draw_square(win->img, x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, color);
            }
		}
	}
}

void	find_player_start(t_map *map, t_vec_double *cord)
{
	unsigned int x;
	unsigned int y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'N' \
                || map->map[y][x] == 'S' \
                || map->map[y][x] == 'E' \
                || map->map[y][x] == 'W') {
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

