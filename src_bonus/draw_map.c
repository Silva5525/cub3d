/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:06:15 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/26 17:10:40 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d(t_c *cub, bool vertical_hit, t_hit *hit, int r)
{
	t_wall	wall;

	wall.texture = NULL;
	calculate_wall_dimensions(hit->distance, &wall);
	select_texture(cub, &wall.texture, hit->vec, vertical_hit);
	wall.tex_x = select_texture_x(cub, wall.texture, hit->vec, vertical_hit);
	draw_wall_slice(cub, r, &wall);
}

static void	pad_map_lines2(t_c *cub, int len, char *new_line)
{
	int	i;

	i = 0;
	while (cub->map[i])
	{
		len = ft_strlen(cub->map[i]);
		if (len < cub->map_width)
		{
			new_line = malloc(cub->map_width + 1);
			if (!new_line)
				er_ex(cub, "Memory allocation failed\n");
			ft_memcpy(new_line, cub->map[i], len);
			ft_memset(new_line + len, ' ', cub->map_width - len);
			new_line[cub->map_width] = '\0';
			free(cub->map[i]);
			cub->map[i] = new_line;
		}
		i++;
	}
}

void	pad_map_lines(t_c *cub)
{
	int		i;
	int		len;
	int		actual_len;

	i = 0;
	while (cub->map[i])
	{
		len = ft_strlen(cub->map[i]);
		actual_len = len;
		while (actual_len > 0 && (cub->map[i][actual_len - 1] == ' '))
			actual_len--;
		if (actual_len > cub->map_width)
			cub->map_width = actual_len;
		i++;
	}
	pad_map_lines2(cub, len, NULL);
}
