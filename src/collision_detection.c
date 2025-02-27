/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:50:15 by mgering           #+#    #+#             */
/*   Updated: 2025/02/27 14:31:18 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	collision(t_c *cub, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_y < 0 || map_x
		>= cub->map_width || map_y >= cub->map_height)
	{
		return (true);
	}
	if (is_wall(cub, x - (PLAYER_SIZE / 2), y - (PLAYER_SIZE / 2))
		|| is_wall(cub, x + (PLAYER_SIZE / 2), y - (PLAYER_SIZE / 2))
		|| is_wall(cub, x - (PLAYER_SIZE / 2), y + (PLAYER_SIZE / 2))
		|| is_wall(cub, x + (PLAYER_SIZE / 2), y + (PLAYER_SIZE / 2)))
	{
		return (true);
	}
	return (false);
}

bool	is_wall(t_c *cub, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_y < 0 || map_x >= cub->map_width
		|| map_y >= cub->map_height)
	{
		return (true);
	}
	return (cub->map[map_y][map_x] == '1');
}
