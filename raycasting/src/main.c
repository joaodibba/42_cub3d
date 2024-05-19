/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:37:36 by rphuyal           #+#    #+#             */
/*   Updated: 2024/05/20 00:42:44 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"
#include "../inc/maps.h"

static void __print_map(int **map, int width, int height) {
    printf("Map:\n");
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            printf("%d", map[i][j]);
        }
        printf("\n");
    }
}

int main(void) {

    int width = L_MAP_W;
    int height = L_MAP_H;

    int **map = (int **)malloc(width * sizeof(int *));
    for (int i = 0; i < height; i++) {
        map[i] = (int *)malloc(width * sizeof(int));
        for (int j = 0; j < width; j++) {
            map[i][j] = largeMap[i][j];
        }
    }
    __print_map(map, width, height);

    // initialize player position and direction
    t_player player;
    player.pos.x = 6;
    player.pos.y = 6;
    player.dir.x = -1;
    player.dir.y = 0;
    player.plane.x = 0;
    player.plane.y = 0.66;

    printf("\nPlayer position: x = %f, y = %f\n", player.pos.x, player.pos.y);
    printf("Player direction: x = %f, y = %f\n", player.dir.x, player.dir.y);

    // init info
    t_info   info;
    info.width = width;
    info.height = height;
    info.map = map;
    int _pixels = -1;
    printf("\nRaycasting...\n");
    while (++_pixels <= width) {
        printf("*** RAYCASTING ON COLUMN %d: \n", _pixels);
        raycast(_pixels, &info, &player);
    }
}