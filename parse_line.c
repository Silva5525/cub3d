/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:35:58 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/24 11:51:52 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	line_err(char *writ)
{
	write(2, "Error\n", 6);
	write(2, writ, ft_strlen(writ));
	return (false);
}

static int	parse_color(char *line, int *color, int i, int out)
{
	color = (int *)malloc(sizeof(int) * 3);
	if (!color)
		return (-1);
	i = 0;
	while (i < 2)
	{
		while (*line == ' ')
			line++;
		while (*line >= '0' && *line <= '9')
		{
			color[i] = color[i] * 10 + (*line - '0');
			line++;
		}
		if (color[i] < 0 || color[i] > 255)
			return (free(color), -1);
		if (*line != ',' || *line == '\0')
			return (free(color), -1);
		if (*line != '\0')
			line++;
		i++;
	}
	out = (150 << 24) | (color[0] << 16) | (color[1] << 8) | color[2];
	return (free(color), out);
}

static int	identifier(char *trim_line, char **path)
{
	if (trim_line == NULL)
		return (-1);
	if (ft_strncmp(trim_line, "NO ", 3) == 0)
		return (*path = &trim_line[3], 0);
	if (ft_strncmp(trim_line, "SO ", 3) == 0)
		return (*path = &trim_line[3], 1);
	if (ft_strncmp(trim_line, "WE ", 3) == 0)
		return (*path = &trim_line[3], 2);
	if (ft_strncmp(trim_line, "EA ", 3) == 0)
		return (*path = &trim_line[3], 3);
	return (4);
}

static bool	direction_line(char *path, t_c *cub,
			mlx_texture_t *texture, int i)
{
	int		len;

	len = strlen(path);
	while (path[len - 1] == ' ')
		len--;
	path[len] = '\0';
	while (*path == ' ')
		path++;
	if (!ft_access_read_write(path, O_RDONLY))
		return (line_err("Texture path not found.\n"));
	texture = mlx_load_png(path);
	if (texture == NULL)
		return (line_err("Texture not found.\n"));
	cub->texture[i].img = mlx_texture_to_image(cub->mlx, texture);
	mlx_delete_texture(texture);
	if (!cub->texture[i].img)
		return (line_err("mlx_texture_to_image failed.\n"));
	return (true);
}

bool	parse_line(char *trim_line, t_c *cub, mlx_texture_t *texture,
			char *path)
{
	int		i;
	int		*color;

	color = NULL;
	if (!cub->mlx)
		return (line_err("No mlx context in parse_line.\n"));
	i = identifier(trim_line, &path);
	if (i == -1)
		return (line_err("identifier in parse_line failed.\n"));
	if (path)
	{
		if (!direction_line(path, cub, texture, i))
			return (line_err("direction_line failed.\n"));
		else
			return (true);
	}
	if (ft_strncmp(trim_line, "F", 1) == 0)
		return (cub->floor = parse_color(trim_line + 2, color, 0, 0), true);
	if (ft_strncmp(trim_line, "C", 1) == 0)
		return (cub->roof = parse_color(trim_line + 2, color, 0, 0), true);
	return (line_err("Invalid line.\n"));
}
