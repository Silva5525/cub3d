/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:24:10 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/18 22:18:01 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_line_helper(bool map, char *line, t_c *cub, ssize_t size)
{
	size_t	len;

	if (map)
	{
		len = ft_strlen(line);
		while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\n'))
			line[--len] = '\0';
		cub->map = ft_realloc(cub->map, sizeof(char *) * size,
				sizeof(char *) * (size + 2));
		if (!cub->map)
			return (-1);
		cub->map[size] = ft_strdup(line);
		if (!cub->map[size])
			return (-1);
		size++;
		cub->map[size] = NULL;
		cub->map_height++;
		if ((int)len > cub->map_width)
			cub->map_width = (int)len;
	}
	else
		if (!parse_line(line, cub, NULL, NULL))
			return (write(2, "Error.\n In parse_line.\n", 23), -1);
	return (size);
}

/// @brief Removes the newline character from the end of the line.
/// and only adds a space if the last character is a map character (wall check).
static char	*end_and_newl_char(char *line)
{
	size_t	len;
	char	*out;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (len > 0 && ft_strchr("01NSEW", line[len - 1]))
	{
		out = ft_strjoin(line, " ");
		free(line);
		return (out);
	}
	return (line);
}

static int	map_line2(char *raw_line, t_c *cub, ssize_t size, bool map)
{
	char	*line;

	line = end_and_newl_char(raw_line);
	if (!line)
		return (-1);
	if (ft_strspn(line, "01NSEW ") == ft_strlen(line))
		map = true;
	else if (map)
		return (free(line), -1);
	size = map_line_helper(map, line, cub, size);
	if (size == -1)
		return (write(2, "MAP_LINE_HELPER\n", 16), free(line), false);
	free(line);
	line = NULL;
	return (size);
}

static bool	map_line(int fd, t_c *cub, ssize_t size, bool map)
{
	char	*raw_line;

	while (1)
	{
		raw_line = get_next_line(fd);
		if (raw_line == NULL)
		{
			free(raw_line);
			break ;
		}
		if (raw_line[0] == '\n')
		{
			free(raw_line);
			continue ;
		}
		size = map_line2(raw_line, cub, size, map);
		if (size == -1)
			return (false);
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
		er_ex(*cub, "Could not open file\n");
	if (!map_line(fd, cub, 0, false))
		return (map_err(NULL, fd));
	close(fd);
	valid_map(cub, 0, 0, 0);
	return (true);
}
