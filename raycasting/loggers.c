/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loggers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:07:50 by rphuyal           #+#    #+#             */
/*   Updated: 2024/06/10 17:22:10 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	__log_computes(t_computes *computes)
{
	printf("-------COMPUTES-------\n");
	printf("ray.x: %f\n", computes->ray.x);
	printf("ray.y: %f\n", computes->ray.y);
	printf("delta.x: %f\n", computes->delta.x);
	printf("delta.y: %f\n", computes->delta.y);
	printf("step.x: %d\n", computes->step.x);
	printf("step.y: %d\n", computes->step.y);
	printf("step_size.x: %f\n", computes->step_size.x);
	printf("step_size.y: %f\n", computes->step_size.y);
	printf("-------------------------\n\n");
}

void	__log_results(t_computes *computes)
{
	printf("------- RESULTS -------\n");
	printf("dir: %c\n", computes->dir);
	printf("side: %d\n", computes->side);
	printf("map.x: %d\n", computes->map.x);
	printf("map.y: %d\n", computes->map.y);
	printf("hit: %d\n", computes->hit);
	printf("dist_to_wall: %f\n", computes->dist_to_wall);
	printf("deltas: x: %f\n", computes->delta.x);
	printf("deltas: y: %f\n", computes->delta.y);
	printf("start_wall: %d\n", computes->start_wall);
	printf("end_wall: %d\n", computes->end_wall);
	printf("wall_height: %d\n", computes->wall_height);
	printf("-------------------------\n\n");
}
