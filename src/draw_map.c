/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:06:15 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/18 22:36:41 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	color_32(t_c *cub, int x, int y)
{
	uint32_t	color;

	if (cub->map[y][x] == '1')
		color = 0x0000009E;
	else
		color = 0x80809E9E;
	return (color);
}

void	draw_map2d(t_c *cub, int x, int y, int ty)
{
	int			tx;
	uint32_t	color;

	while (cub->map[y] != NULL)
	{
		x = 0;
		while (cub->map[y][x] != '\0' && cub->map[y][x] != '\n')
		{
			color = color_32(cub, x, y);
			tx = 0;
			while (tx < TILE_SIZE)
			{
				ty = 0;
				while (ty < TILE_SIZE)
				{
					mlx_put_pixel(cub->mini_map, x * TILE_SIZE + tx,
						y * TILE_SIZE + ty, color);
					ty++;
				}
				tx++;
			}
			x++;
		}
		y++;
	}
}

void	draw_floor_and_ceiling(t_c *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < (HEIGHT / 2))
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(cub->img, x, y, cub->roof);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(cub->img, x, y, cub->floor);
			x++;
		}
		y++;
	}
}

void	draw_3d(t_c *cub, bool vertical_hit, t_hit *hit, int r)
{
	t_wall	wall;

	wall.texture = NULL;
	calculate_wall_dimensions(hit->distance, &wall);
	select_texture(cub, &wall.texture, hit->vec, vertical_hit);
	wall.tex_x = select_texture_x(cub, wall.texture, hit->vec, vertical_hit);
	draw_wall_slice(cub, r, &wall);
}
