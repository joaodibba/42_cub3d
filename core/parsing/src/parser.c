#include "../inc/parser.h"

/*
	@brief Tries to open the file to check if it can be read
	@param path The path to the file
	@return true if the file can be read, false otherwise
*/
bool can_read_file(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

bool parser(char *path, t_window *win, t_map *map)
{
	int map_fd;

	if (!can_read_file(path))
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to read map file: %s\n", path);
		return (false);
	}
	map_fd = open(path, O_RDONLY);
	if (!parse_configs(map_fd, win, map))
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