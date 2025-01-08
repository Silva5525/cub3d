/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:35:58 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/08 20:15:37 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse_line(const char *line, t_c *cub, mlx_texture_t *texture,
			const char *path)
{
	char	*trim_line;

	trim_line = ft_strtrim(line, "\n");
	if (trim_line == NULL)
		return (false);
	if (ft_strncmp(trim_line, "NO ", 3) == 0)
		path = &trim_line[3];
	else if (ft_strncmp(trim_line, "SO ", 3) == 0)
		path = &trim_line[3];
	else if (ft_strncmp(trim_line, "WE ", 3) == 0)
		path = &trim_line[3];
	else if (ft_strncmp(trim_line, "EA ", 3) == 0)
		path = &trim_line[3];
	if (path)
	{
		while (*path == ' ')
			path++;
		if (!ft_access_read_write(path, O_RDONLY))
			return (false);
		texture = mlx_load_png(path);
		if (texture == NULL)
			return (write(2, "Texture File not Found.\n", 24), false);
		// stop for today.. 
	}
}
