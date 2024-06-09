#include "../includes/main.h"


void draw_square_db(t_image *img, double x, double y, int size, int color)
{
    double i;
    double j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            put_pixel(img, x + j, y + i, color);
        }
    }
}

void draw_player(t_image *img, double grid_x, double grid_y, int color)
{
    draw_square_db(img, grid_x * SQUARE_SIZE, grid_y * SQUARE_SIZE, PLAYER_SIZE, color);
}

void	render_2d_map(t_map *map, t_window *win, t_player player)
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
	draw_square_db(win->img, player.pos.x * SQUARE_SIZE, player.pos.y * SQUARE_SIZE, SQUARE_SIZE / 4, 0x00FF0000);
}
