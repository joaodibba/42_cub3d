// ! Missing Header

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