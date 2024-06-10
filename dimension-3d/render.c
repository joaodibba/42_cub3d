/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:28:01 by rphuyal           #+#    #+#             */
/*   Updated: 2024/06/10 18:11:33 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

// Calculate the texture to use for the wall based on the direction
t_image	*get_texture(t_computes *computes, t_map *map)
{
	if (computes->dir == 'N')
		return (map->no);
	else if (computes->dir == 'S')
		return (map->so);
	else if (computes->dir == 'W')
		return (map->we);
	else if (computes->dir == 'E')
		return (map->ea);
	return (NULL);
}

// Calculate the texture position and delta for a pixel on the wall
static double	get_delta_pos(t_image *texture, t_vec_double *pos,
		int wall_height)
{
	double	delta;

	delta = (double)texture->height / wall_height;
	if (wall_height < WIN_HEIGHT)
	{
		pos->y = 0.0;
		return (delta);
	}
	pos->y = (((double)(wall_height - WIN_HEIGHT) / 2) / wall_height) * texture->height;
	delta = 1 - ((double)(wall_height - WIN_HEIGHT) / wall_height);
	delta *= texture->height;
	delta /= WIN_HEIGHT;
	return (delta);
}

// Set the pixel color of the wall texture to the image
void	set_wall_texture(t_image *image, t_cordinates image_cords,
		t_image *texture, t_vec_double texture_pos)
{
	char	*src;
	char	*dest;

	src = texture->addr + ((int)(texture_pos.y) * \
			texture->line_len + (int)(texture_pos.x) * (texture->bpp / 8));
	dest = image->addr + ((int)image_cords.y * \
			image->line_len + (int)(image_cords.x) * (image->bpp / 8));
	*(unsigned int *)dest = *(unsigned int *)src;
}

/*
given the map and the player and the computes
draw the wall for each pixel column with texture
*/
void	create_wall(t_cub *cub, t_image *image, t_computes *computes,
	t_map *map)
{
	double			delta;
	t_image			*texture;
	t_computes		*computed;
	t_cordinates	cords;
	t_vec_double	texture_pos;

	cords = (t_cordinates){-1, -1};
	texture_pos = (t_vec_double){0, 0};
	while (++cords.x < WIN_WIDTH)
	{
		computed = &computes[cords.x];
		texture = get_texture(computed, map);
		if (computed->dir == 'S' || computed->dir == 'W')
			texture_pos.x = ((double)texture->width * (1 - computed->wall_x));
		else
			texture_pos.x = (double)texture->width * computed->wall_x;
		delta = get_delta_pos(texture, &texture_pos, computed->wall_height);
		cords.y = computed->start_wall - 1;
		while (++cords.y < computed->end_wall)
		{
			set_wall_texture(image, cords, texture, texture_pos);
			texture_pos.y += delta;
			if (texture_pos.y >= texture->height - 1)
				break ;
		}
	}
}

void	render_dimension_3d(t_cub *cub)
{
	unsigned int	i;

	i = -1;
	while (++i < WIN_WIDTH)
		raycast(i, cub->map, &cub->player, &cub->cols[i]);
	create_wall(cub, cub->win->img, cub->cols, cub->map);
}
