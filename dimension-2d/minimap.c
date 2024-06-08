#include "../includes/main.h"
#include <stdio.h>
#include <unistd.h>

void	draw_line(t_image *img, t_vec_double *start, t_vec_double *line_len,
		int color)
{
	double			distance;
	t_vec_double	delta;
	t_vec_double	cur;
	double			i;

	distance = sqrt(pow(line_len->x, 2) + pow(line_len->y, 2));
	delta.x = line_len->x / distance;
	delta.y = line_len->y / distance;
	cur.x = start->x;
	cur.y = start->y;
	i = 0;
	while (i <= distance)
	{
		put_pixel(img, (int)floor(cur.x), (int)floor(cur.y), color);
		cur.x += delta.x;
		cur.y += delta.y;
		i++;
	}
}

static void	draw_rays(t_cub *cub)
{
	t_vec_double	player_cord;
	t_vec_double	hit_pos;
	int				i;

	player_cord.x = cub->player.pos.x * SQUARE_SIZE;
	player_cord.y = cub->player.pos.y * SQUARE_SIZE;
	i = -1;
	while (++i < WIN_WIDTH)
	{
		hit_pos.x = cub->cols[i].hit_pos.x * SQUARE_SIZE - player_cord.x;
		hit_pos.y = cub->cols[i].hit_pos.y * SQUARE_SIZE - player_cord.y;
		// printf("at col i : %d | hit_pos.x: %f, hit_pos.y: %f\n", i, hit_pos.x, hit_pos.y);
		draw_line(cub->win->img, &player_cord, &hit_pos, 0x00FFFF00);
	}
}

void	draw_square_db(t_image *img, double x, double y, int size, int color)
{
	double	i;
	double	j;

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

    // Call draw_square to draw a 2x2 square at the calculated position
    draw_square_db(img, grid_x * SQUARE_SIZE, grid_y * SQUARE_SIZE, PLAYER_SIZE, color);
}

void	render_2d_map(t_cub *cub, t_map *map, t_window *win, t_player player)
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
				draw_square(win->img, x * SQUARE_SIZE, y * SQUARE_SIZE,
					SQUARE_SIZE, 0xC8FFFFFF);
			else if (map->map[y][x] && map->map[y][x] == '0')
				draw_square(win->img, x * SQUARE_SIZE, y * SQUARE_SIZE,
					SQUARE_SIZE, 0x00000000);
			else
				draw_square(win->img, x * SQUARE_SIZE, y * SQUARE_SIZE,
					SQUARE_SIZE, 0x00000000); // temporary
			x++;
		}
		y++;
	}
	// draw_rays(cub);
	draw_player(win->img, player.pos.x, player.pos.y, 0x00FF0000);
}
