#include "../inc/parser.h"

// @brief Checks if the string is a valid color
// @param color The string to check 
// @return true if the string is a valid color (between 0 and 255), false otherwise
static bool	is_valid_color(char *color)
{
	int rgb;

	rgb = ft_atoi(color);
	if (rgb < 0 || rgb > 255)
		return (false);
	return (true);
}

// @brief Checks if the string is a digit
// @param str The string to check
// @return true if the string is a digit, false otherwise
static bool ft_isdigit_str(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

// @brief Assigns the value to the color structure
// @param value The string that value to assign to the color
//        The string should be in the format "r,g,b"  where r, g, b are integers between 0 and 255
// @param color The color structure to assign the value to
// @return true if the value was assigned successfully, false otherwise
static bool assign_color(char *value, t_color *color)
{
	char	**rgb;

	rgb = ft_split(value, ',');
	if (!rgb)
		return (false);
	if (ft_array_len(rgb) != 3)
	{
		ft_putendl_fd("Error: Color must be in the format {RRR,GGG,BBB}", STDERR_FILENO);
		ft_free_array(rgb);
		return (false);
	}
	if (!ft_isdigit_str(*rgb) || !is_valid_color(*rgb) || \
		!ft_isdigit_str(*(rgb + 1)) || !is_valid_color(*(rgb + 1)) || \
		!ft_isdigit_str(*(rgb + 2)) || !is_valid_color(*(rgb + 2)))
	{
		ft_putendl_fd("Error: Invalid color, values should be between 0 and 255", STDERR_FILENO);
		ft_free_array(rgb);
		return (false);
	}
	color->red = (u_int8_t)ft_atoi(*rgb);	
	color->green = (u_int8_t)ft_atoi(*(rgb + 1));
	color->blue = (u_int8_t)ft_atoi(*(rgb + 2));
	return (true);
}

bool select_color(char key, char *value, t_map *map)
{
	if (key == 'F')
	{
		if (!assign_color(value, &map->floor))
		{
			ft_putendl_fd("Error: Failed to assign color", STDERR_FILENO);
			return (false);
		}
	}
	else if (key == 'C')
	{
		if (!assign_color(value, &map->ceiling))
		{
			ft_putendl_fd("Error: Failed to assign color", STDERR_FILENO);
			return (false);
		}
	}
	else
	{
		ft_putendl_fd("Error: Invalid key", STDERR_FILENO);
		return (false);
	}
	return (true);
}
