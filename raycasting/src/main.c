/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:37:36 by rphuyal           #+#    #+#             */
/*   Updated: 2024/05/17 00:54:22 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"


int main(void) {
    t_info   info;
    t_player player;
    t_pixel_col pixel_col;

    // configs to test
    char mapTemp[WINDOW_W][WINDOW_H] = {
        {1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1}
    };

    // turn the above map into a 2D array of char pointers
    char **map = (char **)malloc(WINDOW_W * sizeof(char *));
    for (int i = 0; i < WINDOW_W; i++)
        map[i] = mapTemp[i];

    // initialize player position and direction
    player.pos.x = 2;
    player.pos.y = 2;
    player.dir.x = -1;
    player.dir.y = 0;
    player.plane.x = 0;
    player.plane.y = 0.66;

    // init info
    info.width = WINDOW_W;
    info.height = WINDOW_H;
    info.map = map;
    int pixel_count = -1;
    while (++pixel_count < WINDOW_W) {
        raycast(&info, &player, pixel_count);
    }
}