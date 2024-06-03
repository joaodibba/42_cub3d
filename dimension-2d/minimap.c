#include "../includes/main.h"

#define SQUARE_SIZE 50

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_image *img, int x, int y, int size, int color)
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

void	render_2d_map(t_map *map, t_window *win)
{
	int	x;
	int	y;
	int	color;

	for (y = 0; y < map->height; y++)
	{
		for (x = 0; x < map->width; x++)
		{
			if (map->map[y][x] == '1')
				color = 0x00FFFFFF; // white
			else
				color = 0x00000000; // black
			draw_square(win->img, x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, color);
		}
	}
}