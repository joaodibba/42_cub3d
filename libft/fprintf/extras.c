/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:50:16 by rphuyal           #+#    #+#             */
/*   Updated: 2024/05/16 23:51:50 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_fputcharprintf(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int		ft_fputstr(int fd, char *str)
{
	int	len;

	len = 0;
	while (str[len])
		ft_fputcharprintf(fd, str[len++]);
	return (len);
}