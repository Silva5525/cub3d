/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:42:04 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/24 11:49:04 by wdegraf          ###   ########.fr       */
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
		return (0);
	if (view == 'E')
		return (PI);
	return (0);
}


void drawPlayer(t_c *cub)
{
    cub->player.player_img = mlx_new_image(cub->mlx, PLAYER_SIZE, PLAYER_SIZE);
    uint32_t y = 0;
	while (y < PLAYER_SIZE)
	{
		uint32_t x = 0;
		while (x < PLAYER_SIZE)
		{
			mlx_put_pixel(cub->player.player_img, x, y, 0xFF0000FF);
			x++;
		}
		y++;
	}	
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
				cub->player.pos = (t_vector){x + 0.25, y + 0.25};
				cub->player.angle = init_angle(cub->map[y][x]);
				cub->player.delta_pos = (t_vector){cos(cub->player.angle) * 5, sin(cub->player.angle) * 5};
				cub->map[y][x] = '0';
				drawPlayer(cub);
				return ;
			}
			x++;
		}
		y++;
	}
	er_ex(*cub, "No player found in map\n");
}
