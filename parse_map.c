/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:24:10 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/14 10:50:02 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	map_err(char *line, int fd)
{
	write(2, "Error\n", 6);
	write(2, line, ft_strlen(line));
	if (line)
		free(line);
	line = NULL;
	if (fd)
		close(fd);
	return (false);
}

static int	map_line_helper(bool map, char *line, t_c *cub, ssize_t size)
{
	if (map)
	{
		cub->map = ft_realloc(cub->map, sizeof(char *) * size,
				sizeof(char *) * (size + 1));
		if (!cub->map)
			return (-1);
		cub->map[size] = ft_strdup(line);
		size++;
	}
	else
	{
		if (!parse_line(line, cub, NULL, NULL))
			return (write(2, "Error.\n In parse_line.\n", 23), -1);
	}
	line = NULL;
	return (size);
}

/// @brief Overwrites the newline character with a space character.
/// and if the last character of the file is a map character we add 
/// a space character for wall surround check.
static char	*end_and_newl_char(char *line)
{
	size_t	len;
	char	*out;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	out = ft_strjoin(line, " ");
	if (line)
		free(line);
	line = NULL;
	return (out);
}

static bool	map_line(int fd, t_c *cub, ssize_t size, bool map)
{
	char	*line;
	char	*raw_line;

	while (1)
	{
		raw_line = get_next_line(fd);
		if (raw_line == NULL)
			break ;
		if (raw_line[0] == '\n')
			continue ;
		line = end_and_newl_char(raw_line);
		if (ft_strspn(line, "01NSEW ") == ft_strlen(line))
			map = true;
		else if (map)
			return (map_err(line, fd));
		size = map_line_helper(map, line, cub, size);
		if (size == -1)
			return (write(2, "MAP_LINE_HELPER\n", 16), map_err(line, fd));
	}
	cub->map = ft_realloc(cub->map, sizeof(char *) * size,
			sizeof(char *) * (size + 1));
	cub->map[size] = NULL;
	return (true);
}

bool	scan_map(char *file, t_c *cub)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		er_ex(*cub, "Error\nCould not open file\n");
	if (!map_line(fd, cub, 0, false))
		return (close(fd), false);
	close(fd);
	valid_map(cub, 0, 0, 0);
	return (true);
}
