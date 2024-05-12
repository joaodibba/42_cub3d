#include "../inc/parser.h"

// @brief Checks if the key is a texture
// @param key The key to check
// @return true if the key is a texture, false otherwise
static bool	is_texture(char *key)
{
	return (!ft_strcmp(key, "NO") || !ft_strcmp(key, "SO")
		|| !ft_strcmp(key, "WE") || !ft_strcmp(key, "EA"));
}

// @brief Assigns the value to the texture structure
// @param value The string that value to assign to the texture
// @param texture The texture structure to assign the value to
// @return true if the value was assigned successfully, false otherwise
static bool assign_texture(char *value, t_image *texture)
{
	texture->path = ft_strdup(value);
	if (!texture->path)
		return (false);
	return (true);
}