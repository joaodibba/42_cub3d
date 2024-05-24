#include "../inc/parser.h"

bool parser(char *path, t_window *win, t_map *map)
{
	int map_fd;

	map_fd = open(path, O_RDONLY);
	if (map_fd < 0)
	{
		ft_fprintf(STDERR_FILENO, "Error: %s\n", strerror(errno));
		return (false);
	}
	if (!parse_configs(map_fd, &win, &map))
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to parse configs. Please check the map file.\n");
		close(map_fd);
		return (false);
	}
	
	if (!parse_map(map_fd, &(map->map)))
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to parse map: %s\n", path);
		close(map_fd);
		return (false);
	}
	close(map_fd);
	return (true);
}