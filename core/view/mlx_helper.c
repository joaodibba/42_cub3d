#include "../../includes/main.h"

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

void	paint_window(t_window *win, int ceiling_color, int floor_color)
{
    int x;
    int y;

    // Paint the top half with the given color
	y = 0;
    while (y < WIN_HEIGHT / 2)
    {
        x = 0;
        while (x < WIN_WIDTH)
            put_pixel(win->img, x++, y, ceiling_color);
        y++;
    }
    y = WIN_HEIGHT / 2;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
            put_pixel(win->img, x++, y, floor_color);
        y++;
    }
}