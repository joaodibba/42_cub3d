/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loggers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:07:50 by rphuyal           #+#    #+#             */
/*   Updated: 2024/05/17 11:25:56 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"

void __log_computes(t_computes *computes) {
	printf("-------COMPUTES-------\n");
	printf("ray.x: %f\n", computes->ray.x);
	printf("ray.y: %f\n", computes->ray.y);
	printf("delta.x: %f\n", computes->delta.x);
	printf("delta.y: %f\n", computes->delta.y);
	printf("step.x: %d\n", computes->step.x);
	printf("step.y: %d\n", computes->step.y);
	printf("side_dist.x: %f\n", computes->side_dist.x);
	printf("side_dist.y: %f\n", computes->side_dist.y);
}

void __log_results(t_computes *computes) {
    printf("------- RESULTS -------\n");
	printf("side: %d\n", computes->side);
	printf("map.x: %d\n", computes->map.x);
	printf("map.y: %d\n", computes->map.y);
	printf("-------------------------\n\n");
}