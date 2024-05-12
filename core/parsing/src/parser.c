#include "../inc/parser.h"

bool parser(char *path, t_window *win, t_map *map)
{
	int map_fd;

	map_fd = open(path, O_RDONLY);
	if (map_fd < 0)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (false);
	}
	if (!parse_configs(map_fd, &win, &map))
	{
		ft_putendl_fd("Error: Failed to parse configs.", STDERR_FILENO);
		close(map_fd);
		return (false);
	}
	
	if (!parse_map(map_fd, &(map->map)))
	{
		ft_putendl_fd("Error: Failed to parse map.", STDERR_FILENO);
		close(map_fd);
		return (false);
	}
	close(map_fd);
	return (true);
}