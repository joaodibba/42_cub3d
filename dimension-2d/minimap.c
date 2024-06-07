#include "../includes/view.h"

void	render_2d_map(t_map *map, t_window *win)
{
	int	x;
	int	y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] && map->map[y][x] == '1')
				draw_square(win->img, x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, 0xC8FFFFFF);
			else if (map->map[y][x] && map->map[y][x] == '0')
				draw_square(win->img, x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, 0x00000000);
			else
				draw_square(win->img, x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, 0x00000000); // temporary
			x++;
		}
		y++;
	}
	// draw_square(win->img, (int)win->cub->player.pos.x * SQUARE_SIZE, (int)win->cub->player.pos.y * SQUARE_SIZE, SQUARE_SIZE, 0x00FF0000);
}
