/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:42:04 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/24 11:54:32 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	t_vector	init_dir(char view)
{
	if (view == 'N')
		return ((t_vector){0, -1});
	if (view == 'S')
		return ((t_vector){0, 1});
	if (view == 'W')
		return ((t_vector){-1, 0});
	if (view == 'E')
		return ((t_vector){1, 0});
	return ((t_vector){0, 0});
}

static t_vector	init_plane(char view)
{
	if (view == 'N')
		return ((t_vector){0.66, 0});
	if (view == 'S')
		return ((t_vector){-0.66, 0});
	if (view == 'W')
		return ((t_vector){0, -0.66});
	if (view == 'E')
		return ((t_vector){0, 0.66});
	return ((t_vector){0, 0});
}

void	create_player(t_c *cub, int x, int y)
{
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (ft_strchr("NSWE", cub->map[y][x]))
			{
				cub->player.pos = (t_vector){x + 0.5, y + 0.5};
				cub->player.dir = init_dir(cub->map[y][x]);
				cub->player.plane = init_plane(cub->map[y][x]);
				cub->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
	er_ex(*cub, "No player found in map\n");
}
