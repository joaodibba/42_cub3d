#include "../includes/main.h"
# include <stdio.h>
# include <stdlib.h>

void    choose_texture(t_image **texture, t_computes *computes, t_map *map)
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

/*
given the map and the player and the computes
draw the wall for each pixel column. with color or texture
*/
void    create_wall(t_cub *cub, t_image *image, t_computes *computes, t_map *map, t_player *player)
{
    unsigned int    i;
    unsigned int    j;
    unsigned int    color;
    t_image         *texture;

    i = -1;
    color = 0x0000FF00;
    while (++i < WIN_WIDTH)
    {
        // printf("computes[%d].wall_x: %f\n", i, computes[i].wall_x);
        if (computes[i].wall_x == 0)
            color = 0x00FF0000;
        else if (computes[i].dir == 'N')
            color = 0x00000000;
        else if (computes[i].dir == 'S')
            color = 0x0000FF00;
        else if (computes[i].dir == 'W')
            color = 0x000000FF;
        else if (computes[i].dir == 'E')
            color = 0x00FF00FF;

        j = -1;
        while (++j < WIN_HEIGHT)
        {
			if (j < computes[i].start_wall || j > computes[i].end_wall)
                continue ;
            choose_texture(&texture, &computes[i], map);
            // int x_tex = (int)(computes[i].wall_x * (double)texture->width);
            // int y_tex = (int)(j * (double)texture->height / computes[i].wall_height);
            // char *dst =  (cub->win->img)->addr + (j * (cub->win->img)->line_len + i * ((cub->win->img)->bpp / 8));
            // printf("what is this: %d\n", *(unsigned int *)(texture->addr + (y_tex * texture->line_len + x_tex * (texture->bpp / 8))));
            // *(unsigned int *)dst = *(unsigned int *)(texture->addr + (y_tex * texture->line_len + x_tex * (texture->bpp / 8)));
            put_pixel(image, i, j, color);
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