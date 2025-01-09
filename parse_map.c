/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:24:10 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/09 19:53:11 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	map_err(char *line, int fd)
{
	write(2, "Error\n", 6);
	write(2, line, ft_strlen(line));
	if (line)
		free(line);
	if (fd)
		close(fd);
	return (false);
}

static bool	map_line_helper(bool map, char *line, t_c *cub, size_t size)
{
	printf("map: %d\n", map);
	if (map)
	{
		cub->map = ft_realloc(cub->map, sizeof(char *) * size,
				sizeof(char *) * (size + 1));
		if (!cub->map)
			return (false);
		cub->map[size++] = ft_strdup(line);
		size++;
	}
	else
	{
		printf("parse_line\n");
		if (!parse_line(line, cub, NULL, NULL))
			return (write(2, "else map_line_helper\n", 21), false);
	}

	free(line);
	line = NULL;
	return (true);
}

static bool	map_line(int fd, t_c *cub, size_t size, size_t len)
{
	char	*line;
	bool	map;

	map = false;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] == '\n')
			continue ;
		if (ft_strspn(line, "1NSEW") == ft_strlen(line))
			map = true;
		else if (map)
			return (map_err(line, fd));
		if (!map_line_helper(map, line, cub, size))
			return (write(2, "MAP_LINE_HELPER\n", 16), map_err(line, fd));
	}
	free(line);
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
		er_ex(*cub, "Error\nCould not open file");
	if (!map_line(fd, cub, 0, 0))
		return (close(fd), false);
	close(fd);
	// vilid_map(cub);
	return (true);
}
