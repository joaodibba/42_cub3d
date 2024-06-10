#include "../includes/main.h"
# include <stdio.h>
# include <stdlib.h>

void    __color(unsigned int *color, t_computes *computes)
{
    if (computes->dir == 'N')
        *color = 0x00DF0F0F;
    else if (computes->dir == 'S')
        *color = 0x0000FF00;
    else if (computes->dir == 'W')
        *color = 0x000FF0FF;
    else if (computes->dir == 'E')
        *color = 0x00FF00FF;
}

void    __get_texture(t_image **texture, t_computes *computes, t_map *map)
{
    if (computes->dir == 'N')
        *texture = map->no;
    else if (computes->dir == 'S')
        *texture = map->so;
    else if (computes->dir == 'W')
        *texture = map->we;
    else if (computes->dir == 'E')
        *texture = map->ea;
}

unsigned int    get_pixel(t_image *texture, int x, int y)
{
    return (*(unsigned int *)(texture->addr + (y * texture->line_len + x * (texture->bpp / 8))));
}


// Calculate the texture position and step for drawing the wall
static void calculate_close_to_wall(t_vec_double *texture_pos, double *delta, int columnHeight, int textureHeight)
{
    // Calculate the texture position along the y-axis
    texture_pos->y = (((columnHeight - WIN_HEIGHT) / 2) / columnHeight) * textureHeight;

    // Calculate the delta size for incrementing the texture position
    *delta = 1 - ((columnHeight - WIN_HEIGHT) / columnHeight);
    *delta *= textureHeight;
    *delta /= WIN_HEIGHT;
}

/*
given the map and the player and the computes
draw the wall for each pixel column. with color or texture
*/
void    create_wall(t_cub *cub, t_image *image, t_computes *computes, t_map *map, t_player *player)
{
    unsigned int    i;
    unsigned int    j;
    unsigned int    color;
    t_computes		*computed;
    t_image         *texture;

    i = -1;
    while (++i < WIN_WIDTH)
    {
		computed = &computes[i];
        __get_texture(&texture, computed, map);
        t_vec_double window_vec = (t_vec_double){i, computed->start_wall};
        t_vec_double texture_pos = (t_vec_double){0, 0};

        if (computed->dir == 'N' || computed->dir == 'E')
            texture_pos.x = (double)texture->width * computed->wall_x;
        else
            texture_pos.x = ((double)texture->width * (1.0 - computed->wall_x));

        double delta = 1.0 * texture->height / computed->wall_height;

        if (computed->wall_height < WIN_HEIGHT)
            texture_pos.y = 0.0;
        else
            calculate_close_to_wall(&texture_pos, &delta, computed->wall_height, texture->height);

        j = computed->start_wall - 1;
        while (++j < computed->end_wall)
        {
			char *text_pxl = texture->addr + ((int)(texture_pos.y) * texture->line_len
					+ (int)(texture_pos.x) * (texture->bpp / 8));
			char *win_pxl = image->addr + (j * image->line_len
					+ (int)(i) * (image->bpp / 8));
			*(unsigned int *)win_pxl = *(unsigned int *)text_pxl;
			texture_pos.y += delta;
        }
    }
}

void	render_dimension_3d(t_cub *cub)
{
	unsigned int	i;

	i = -1;
	while (++i < WIN_WIDTH)
		raycast(i, cub->map, &cub->player, &cub->cols[i]);
	create_wall(cub, cub->win->img, cub->cols, cub->map, &cub->player);
}