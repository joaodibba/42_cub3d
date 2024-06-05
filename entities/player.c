#include "../includes/main.h"

#include "../includes/main.h"

#define SQUARE_SIZE 50

void	_put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	_draw_square(t_image *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			put_pixel(img, x + j, y + i, color);
		}
	}
}

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
                _draw_square(win->img, x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, color);
            }
		}
	}
}

