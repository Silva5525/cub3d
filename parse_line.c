/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:35:58 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/09 19:52:31 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	line_err(char *writ, char *trim_line)
{
	write(2, "Error\n", 6);
	write(2, writ, ft_strlen(writ));
	if (trim_line)
		free(trim_line);
	return (false);
}

/// @brief 
/// @param line 
/// @param color 
/// @return 
static int	parse_color(const char *line, int color[3])
{
	int		i;

	i = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		while (*line >= '0' && *line <= '9')
		{
			color[i] = color[i] * 10 + (*line - '0');
			line++;
		}
		if (color[i] < 0 || color[i] > 255)
			return (-1);
		if (*line != ',' || *line == '\0')
			return (-1);
		if (*line != '\0')
			line++;
		i++;
	}
	color[i] = 150;
	return ((color[3] << 24) | (color[0] << 16) | (color[1] << 8) | color[2]);
}

static int	identifier(char *trim_line, const char *path)
{
	if (trim_line == NULL)
		return (-1);
	if (ft_strncmp(trim_line, "NO ", 3) == 0)
		return (path = &trim_line[3], 0);
	if (ft_strncmp(trim_line, "SO ", 3) == 0)
		return (path = &trim_line[3], 1);
	if (ft_strncmp(trim_line, "WE ", 3) == 0)
		return (path = &trim_line[3], 2);
	if (ft_strncmp(trim_line, "EA ", 3) == 0)
		return (path = &trim_line[3], 3);
	return (4);
}

static bool	direction_line(const char *path, t_c *cub,
			mlx_texture_t *texture, int i)
{
	if (path)
	{
		while (*path == ' ')
			path++;
		if (!ft_access_read_write(path, O_RDONLY))
			return (line_err("Texture path not found.\n", NULL));
		texture = mlx_load_png(path);
		if (texture == NULL)
			return (line_err("Texture not found.\n", NULL));
		cub->texture[i].img = mlx_texture_to_image(cub->mlx, texture);
		mlx_delete_texture(texture);
		if (!cub->texture[i].img)
			return (line_err("mlx_texture_to_image failed.\n", NULL));
		return (true);
	}
}

bool	parse_line(const char *line, t_c *cub, mlx_texture_t *texture,
			char *path)
{
	char	*trim_line;
	int		i;

	printf("parse_line\n"); // debug
	if (!cub->mlx)
		return (line_err("No mlx context in parse_line.\n", NULL));
	trim_line = ft_strtrim(line, "\n");
	printf("line: %s\n", trim_line); // debug
	i = identifier(trim_line, path);
	if (i == -1)
		return (line_err("identifier in parse_line failed.\n", trim_line));
	if (direction_line(path, cub, texture, i))
		return (line_err("direction_line failed.\n", trim_line));
	else
		return (free(trim_line), true);
	if (ft_strncmp(trim_line, "F", 1) == 0)
		return (cub->floor = parse_color(trim_line + 2, 0),
			free(trim_line), true);
	if (ft_strncmp(trim_line, "C", 1) == 0)
		return (cub->roof = parse_color(trim_line + 2, 0),
			free(trim_line), true);
	return (line_err("Invalid line.\n", trim_line));
}
