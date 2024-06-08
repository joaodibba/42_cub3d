#include "../includes/view.h"
# include <stdio.h>
# include <stdlib.h>
// void   get_texture_color(t_texture *texture, int x, int y)
// {
//     int     color;
//     int     i;
//     int     j;

//     i = x;
//     j = y;
//     color = texture->data[j * texture->width + i];
//     return (color);
// }

// void    get_wall_color(t_computes *computes, t_map *map, t_player *player, int i, int j)
// {
//     int     color;
//     int     x;
//     int     y;

//     x = computes->wall_x;
//     y = computes->wall_y;
//     if (computes->dir == 'N')
//         color = get_texture_color(map->no, x, y);
//     else if (computes->dir == 'S')
//         color = get_texture_color(map->so, x, y);
//     else if (computes->dir == 'W')
//         color = get_texture_color(map->we, x, y);
//     else if (computes->dir == 'E')
//         color = get_texture_color(map->ea, x, y);
//     return (color);
// }

/*
given the map and the player and the computes
draw the wall for each pixel column. with color or texture
*/
void    create_wall(t_image *image, t_computes *computes, t_map *map, t_player *player)
{
    unsigned int    i;
    unsigned int    j;
    unsigned int    color;

    i = -1;
    color = 0x0000FF00;
    while (++i < WIN_WIDTH)
    {
        j = -1;
        while (++j < WIN_HEIGHT)
        {
			if (j < computes[i].start_wall || j > computes[i].end_wall)
                continue ;

			if (computes[i].dir == 'N')
				color = 0x00000000;
			else if (computes[i].dir == 'S')
				color = 0x0000FF00;
			else if (computes[i].dir == 'W')
				color = 0x000000FF;
			else if (computes[i].dir == 'E')
				color = 0x00FF00FF;
            put_pixel(image, i, j, color);
        }
    }
}

