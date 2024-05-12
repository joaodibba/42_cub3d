// ! Missing Header

#include "../libft.h"

// @brief Get the length of an array of strings
// @param array The array of strings
size_t ft_array_len(char **array)
{
	size_t len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}