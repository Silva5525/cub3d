/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:42:04 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/18 22:44:07 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	init_angle(char view)
{
	if (view == 'N')
		return (1.5 * PI);
	if (view == 'S')
		return (0.5 * PI);
	if (view == 'W')
		return (PI);
	if (view == 'E')
		return (0);
	return (0);
}

void	init_player(t_c *cub, int x, int y)
{
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (ft_strchr("NSWE", cub->map[y][x]))
			{
				cub->player.pos = (t_vector){x + 0.25, y + 0.25};
				cub->player.angle = init_angle(cub->map[y][x]);
				cub->player.delta_pos = (t_vector){cos(cub->player.angle) * 5,
					sin(cub->player.angle) * 5};
				cub->map[y][x] = '0';
				cub->last_angle = -1;
				return ;
			}
			x++;
		}
		y++;
	}
	er_ex(cub, "No player found in map\n");
}
