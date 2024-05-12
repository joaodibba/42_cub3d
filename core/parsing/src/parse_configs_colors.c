#include "../inc/parser.h"

// @brief Checks if the key is a color
// @param key The key to check
// @return true if the key is a color, false otherwise
static bool is_color(char *key)
{
	return (!ft_strcmp(key, "F") || !ft_strcmp(key, "C"));
}

// @brief Checks if the value is a valid color
// @param color The color to check
// @return true if the color is valid, false otherwise
static bool	is_valid_color(int color)
{
	return (color >= 0 && color <= 255);
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
		ft_free_array(rgb);
		return (false);
	}
	color->red = (u_int8_t)ft_atoi(*rgb);
	color->green = (u_int8_t)ft_atoi(*(rgb + 1));
	color->blue = (u_int8_t)ft_atoi(*(rgb + 2));
	if (!is_valid_color(color->red) || !is_valid_color(color->green) || !is_valid_color(color->blue))
	{
		ft_free_array(rgb);
		return (false);
	}
	return (true);
}