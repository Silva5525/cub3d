/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:24:10 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/08 15:57:27 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	map_err(char *line, int fd)
{
	write(2, "Error\n", 6);
	write(2, line, ft_strlen(line));
	free(line);
	close(fd);
	return (false);
}

static bool	*map_line_helper(bool map, char *line, t_c *cub, size_t size)
{
	if (map)
	{
		cub->map = ft_realloc(cub->map, sizeof(char *) * size,
				sizeof(char *) * (size + 1));
		if (!cub->map)
			return (false);
		cub->map[size++] = ft_strdub(line);
		size++;
	}
	else
		if (!parse_line(line, cub, NULL, NULL))
			return (false);
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
		if (ft_strspn(line, "1NSEW") != ft_strlen(line))
			map = true;
		else if (map)
			return (map_err(line, fd));
		if (!map_line_helper(map, line, cub, size))
			return (map_err("map_line_helper", fd));
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

	/// check if map is valid

	return (true);
}
