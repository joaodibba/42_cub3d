/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:50:03 by rphuyal           #+#    #+#             */
/*   Updated: 2024/06/11 19:10:29 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	draw_line(t_image *img, t_vec_double *start, t_vec_double *line_len,
		int color)
{
	t_vec_double	cur;
	t_vec_double	iter;
	t_vec_double	delta;

	iter = (t_vec_double){-1, sqrt(pow(line_len->x, 2) + pow(line_len->y, 2))};
	cur = (t_vec_double){start->x, start->y};
	delta = (t_vec_double){line_len->x / iter.y, line_len->y / iter.y};
	while (++iter.x <= iter.y)
	{
		put_pixel(img, (int)floor(cur.x), (int)floor(cur.y), color);
		cur.x += delta.x;
		cur.y += delta.y;
	}
}

static void	draw_rays(t_cub *cub)
{
	t_vec_double	player_cord;
	t_vec_double	hit_cord;
	int				i;

	player_cord.x = cub->player.pos.x * SQUARE_SIZE;
	player_cord.y = cub->player.pos.y * SQUARE_SIZE;
	i = -1;
	while (++i < WIN_WIDTH)
	{
		hit_cord.x = cub->cols[i].hit_pos.x * SQUARE_SIZE - player_cord.x;
		hit_cord.y = cub->cols[i].hit_pos.y * SQUARE_SIZE - player_cord.y;
		draw_line(cub->win->img, &player_cord, &hit_cord, 0x00FFFF66);
	}
}

void	draw_square_db(t_image *img, double x, double y, int size)
{
	double	i;
	double	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(img, x + j, y + i, 0x00FF0000);
			j++;
		}
		i++;
	}
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
				draw_square(win->img, (t_cordinates){x * SQUARE_SIZE, y
					* SQUARE_SIZE}, SQUARE_SIZE, 0xC8FFFFFF);
			else if (map->map[y][x] && map->map[y][x] == '0')
				draw_square(win->img, (t_cordinates){x * SQUARE_SIZE, y
					* SQUARE_SIZE}, SQUARE_SIZE, 0x00000000);
			x++;
		}
		y++;
	}
	draw_rays(cub);
	draw_square_db(win->img, player.pos.x * SQUARE_SIZE, player.pos.y
		* SQUARE_SIZE, SQUARE_SIZE / 4);
}
