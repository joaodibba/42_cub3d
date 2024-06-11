/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:31:52 by rphuyal           #+#    #+#             */
/*   Updated: 2024/06/10 20:32:15 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// @brief Free the array of strings
// @param array The array of strings to free
void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
