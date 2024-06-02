/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:09:55 by rphuyal           #+#    #+#             */
/*   Updated: 2024/06/01 18:55:14 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"

void	__move() {
	    int     _x;
    int     _y;

    _x = (int)(player->pos.x - player->dir.x * player->speed);
    _y = (int)(player->pos.y - player->dir.y * player->speed);
}

void    move_forward(t_player *player, int **map) {
    int     _x;
    int     _y;
	double	speed;

	speed = 0.4f;
    _x = (int)(player->pos.x + player->dir.x * speed);
    _y = (int)(player->pos.y + player->dir.y * speed);

    if (map[_x][(int)player->pos.y] == 0)
        player->pos.x += player->dir.x * speed;
    if (map[(int)player->pos.x][_y] == 0)
        player->pos.y += player->dir.y * speed;
}

void    move_backward(t_player *player, int **map) {
    int     _x;
    int     _y;
	double	speed;

	speed = 0.4f;
    _x = (int)(player->pos.x - player->dir.x * speed);
    _y = (int)(player->pos.y - player->dir.y * speed);

    if (map[_x][(int)player->pos.y] == 0)
        player->pos.x -= player->dir.x * speed;
    if (map[(int)player->pos.x][_y] == 0)
        player->pos.y -= player->dir.y * speed;
}

void	move_right(t_player *player, double angle) {
	__rotate_vector(player->dir, -angle);
	__rotate_vector(player->plane, -angle);
}

void	move_left(t_player *player, double angle) {
	__rotate_vector(player->dir, angle);
	__rotate_vector(player->plane, angle);
}
