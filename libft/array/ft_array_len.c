/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:25:59 by rphuyal           #+#    #+#             */
/*   Updated: 2024/06/10 20:29:55 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// @brief Get the length of an array of strings
// @param array The array of strings
size_t	ft_array_len(char **array)
{
	size_t	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}
