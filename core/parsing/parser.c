/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:02:43 by jalves-c          #+#    #+#             */
/*   Updated: 2024/06/10 21:02:46 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

bool	parse_map(int map_fd, t_map **map);
bool	parse_configs(int map_fd, t_window *win, t_map *map);
bool	is_line_empty(char *line);
bool	check_borders(char **map, int i, int j);

void	null_map_confs(t_map *map)
{
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->map = NULL;
}

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
	{
		free_cub(cub);
		ft_fprintf(STDERR_FILENO, "Error: Failed to read map file: %s\n", path);
		return (false);
	}
	map_fd = open(path, O_RDONLY);
	if (map_fd == -1 || !parse_configs(map_fd, win, map))
	{
		free_cub(cub);
		ft_fprintf(STDERR_FILENO, \
			"Error: Failed to parse configs. Please check the map file.\n");
		close(map_fd);
		return (false);
	}
	if (!parse_map(map_fd, &map))
	{
		free_cub(cub);
		ft_fprintf(STDERR_FILENO, "Error: Failed to parse map: %s\n", path);
		close(map_fd);
		return (false);
	}
	close(map_fd);
	return (true);
}
