/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:13:57 by mgering           #+#    #+#             */
/*   Updated: 2025/02/27 17:25:26 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	get_map_char(t_c *cub, int x, int y)
{
	if (y < 0 || y >= cub->map_height || !cub->map[y])
		return ('1');
	if (x < 0 || x >= (int)ft_strlen(cub->map[y]))
		return ('1');
	return (cub->map[y][x]);
}

void	put_pixel_on_change(t_c *cub, int x, int y, uint32_t color)
{
	int	index;

	index = y * WIDTH + x;
	if (cub->last_frame_pixel[index] != color)
	{
		mlx_put_pixel(cub->img, x, y, color);
		cub->last_frame_pixel[index] = color;
	}
}
