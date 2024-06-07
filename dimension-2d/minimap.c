#include "../includes/main.h"

void	render_2d_map(t_map *map, t_window *win)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] && map->map[y][x] == '1')
				color = 0xC8FFFFFF; // white
			else if (map->map[y][x] && ( map->map[y][x] == '0' || is_valid_player_char(map->map[y][x])))
				color = 0x00000001; // black
			else
				color = 0x00000000;
			if (color != 0x00000000)
				draw_square(win->img, x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, color);
			x++;
		}
		y++;
	}
}
