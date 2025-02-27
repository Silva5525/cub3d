/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:04:05 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/27 17:17:28 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	map_err(char *line, int fd)
{
	write(2, "Error\n", 6);
	if (line)
	{
		write(2, line, ft_strlen(line));
		free(line);
	}
	line = NULL;
	if (fd)
		close(fd);
	return (false);
}

static bool	map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

static bool	wall_surround(t_c *cub, int x, int y)
{
	return (cub->map[y - 1][x] != ' ' && cub->map[y + 1][x] != ' ' &&
		cub->map[y][x - 1] != ' ' && cub->map[y][x + 1] != ' ');
}

static bool	wall_cells(t_c *cub, int x, int y)
{
	if (cub->map[y][x] != '1' && cub->map[y][x] != ' ')
	{
		if (y == 0 || cub->map[y + 1] == NULL || x == 0
			|| cub->map[y][x + 1] == '\0')
			return (ft_printf("Error\nMap is not enclosed at %d, %d\n",
					x, y), false);
		if (!wall_surround(cub, x, y))
			return (ft_printf("Error\nMap is not surroundet at %d, %d\n",
					x, y), false);
	}
	return (true);
}

bool	valid_map(t_c *cub, int p_count, int x, int y)
{
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (!map_char(cub->map[y][x]))
				return (ft_printf("Invalid character '%c' at (%d, %d)\n",
						cub->map[y][x], x, y), false);
			if (!wall_cells(cub, x, y))
				return (ft_printf("Error at cell (%d, %d)\n", x, y), false);
			if (ft_strchr("NSEW", cub->map[y][x]))
				if (++p_count > 1)
					return (write(2, "Error\nToo many players\n", 23), false);
			x++;
		}
		y++;
	}
	if (ft_fill(cub->map, (t_xy){cub->map_width, cub->map_height},
		(t_xy){x, y}))
		return (write(2, "Error\nMap is not enclosed vald_map\n", 26), false);
	return (p_count == 1);
}
