/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:02:43 by jalves-c          #+#    #+#             */
/*   Updated: 2024/06/11 16:34:01 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

bool	parse_map(int map_fd, t_map **map);
bool	parse_configs(int map_fd, t_window *win, t_map *map);
bool	is_line_empty(char *line);
bool	check_borders(char **map, int i, int j);
void	null_map_confs(t_map *map);

bool	check_file_format(char *file, char *format)
{
	char	*str;

	str = ft_strrchr(file, '.');
	if (str && !ft_strncmp(str, format, ft_strlen(file)))
		return (true);
	return (false);
}

/*
	@brief Tries to open the file to check if it can be read
	@param path The path to the file
	@return true if the file can be read, false otherwise
*/
bool	can_read_file(char *path, char *format)
{
	int	fd;

	fd = -1;
	if (!check_file_format(path, format))
		return (false);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

bool	do_stuff(t_cub *cub, int map_fd, char *path)
{
	free_cub(cub);
	ft_fprintf(STDERR_FILENO, "Error: %s\n", path);
	if (map_fd != -1)
		close(map_fd);
	return (false);
}

/*
	@brief Parses the map file
	@param path The path to the map file
	@param win The window struct
	@param map The map struct
	@return true if the map file was parsed successfully, false otherwise
*/
bool	parser(t_cub *cub, char *path, t_window *win, t_map *map)
{
	int	map_fd;

	map_fd = -1;
	null_map_confs(map);
	if (!can_read_file(path, ".cub"))
		return (do_stuff(cub, map_fd, "Failed to read map file"));
	map_fd = open(path, O_RDONLY);
	if (map_fd == -1 || !parse_configs(map_fd, win, map))
		return (do_stuff(cub, map_fd, "Failed to parse configs"));
	if (!parse_map(map_fd, &map))
		return (do_stuff(cub, map_fd, "Failed to parse map"));
	close(map_fd);
	return (true);
}
