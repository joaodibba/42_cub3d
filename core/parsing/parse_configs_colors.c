/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs_colors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:03:11 by jalves-c          #+#    #+#             */
/*   Updated: 2024/06/10 21:45:12 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

/*
	@brief Checks if the string is a valid color
	@param color The string to check
	@return true if the string is a valid color (between 0 and 255),
		false otherwise
*/
static bool	is_valid_color(char *color)
{
	int	rgb;

	rgb = ft_atoi(color);
	if (rgb < 0 || rgb > 255)
		return (false);
	return (true);
}

/*
	@brief Checks if the string is a digit
	@param str The string to check
	@return true if the string is a digit, false otherwise
*/
static bool	ft_isdigit_str(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

/*
	@brief Assigns the value to the color structure
	@param value The string that value to assign to the color
	@param The string should be in the format "r,g,b"  where r, g,
		b are integers between 0 and 255
	color The color structure to assign the value to
	@return true if the value was assigned successfully, false otherwise
*/
static bool	assign_color(char *value, unsigned int *color)
{
	char	**rgb;

	rgb = ft_split(value, ',');
	if (!rgb)
		return (false);
	if (ft_array_len(rgb) != 3)
	{
		ft_fprintf(STDERR_FILENO, \
			"Error: Color must be in the format {RRR,GGG,BBB}\n");
		ft_free_array(rgb);
		return (false);
	}
	if (!ft_isdigit_str(*rgb) || !is_valid_color(*rgb) || \
		!ft_isdigit_str(*(rgb + 1)) || !is_valid_color(*(rgb + 1)) || \
		!ft_isdigit_str(*(rgb + 2)) || !is_valid_color(*(rgb + 2)))
	{
		ft_fprintf(STDERR_FILENO, \
			"Error: Invalid color, values should be between 0 and 255\n");
		ft_free_array(rgb);
		return (false);
	}
	*color = rgb_to_hex(ft_atoi(*rgb), ft_atoi(*(rgb + 1)), \
		ft_atoi(*(rgb + 2)));
	ft_free_array(rgb);
	return (true);
}

static bool	check_and_assign_color(char *value, unsigned int *color_field, \
	const char *error_message)
{
	if (*color_field != 0)
	{
		ft_fprintf(STDERR_FILENO, error_message);
		return (false);
	}
	else if (!assign_color(value, color_field))
	{
		ft_fprintf(STDERR_FILENO, "Error: Invalid color key\n");
		return (false);
	}
	return (true);
}

/*
	@brief Parses the color configuration
	@param key The key of the configuration
	@param value The value of the configuration
	@param map The map structure to assign the color to
	@return true if the color was assigned successfully, false otherwise
*/
bool	select_color(char key, char *value, t_map *map)
{
	if (key == 'F')
		return (check_and_assign_color(value, &map->floor, \
			"Error: Floor color code specified more than once.\n"));
	else if (key == 'C')
		return (check_and_assign_color(value, &map->ceiling, \
			"Error: Ceiling color code specified more than once.\n"));
	else
	{
		ft_fprintf(STDERR_FILENO, "Error: Invalid color key\n");
		return (false);
	}
}
