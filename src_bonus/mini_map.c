/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:58:17 by mgering           #+#    #+#             */
/*   Updated: 2025/02/27 17:24:05 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_tile(t_c *cub, int dest_x, int dest_y, uint32_t color)
{
	int	px;
	int	py;

	py = 0;
	while (py < MINIMAP_TILE_SIZE)
	{
		px = 0;
		while (px < MINIMAP_TILE_SIZE)
		{
			put_pixel_on_change(cub, dest_x + px, dest_y + py, color);
			px++;
		}
		py++;
	}
}

static void	draw_minimap_tiles(t_c *cub, t_minimap minimap)
{
	int			tile_x;
	int			tile_y;
	int			map_x;
	int			map_y;
	uint32_t	color;

	tile_y = 0;
	while (tile_y < minimap.tiles_y)
	{
		tile_x = 0;
		while (tile_x < minimap.tiles_x)
		{
			map_x = minimap.start_x + tile_x;
			map_y = minimap.start_y + tile_y;
			if (get_map_char(cub, map_x, map_y) == '1'
				|| get_map_char(cub, map_x, map_y) == ' ')
				color = 0x0000009E;
			else
				color = 0x80809E9E;
			draw_tile(cub, tile_x * MINIMAP_TILE_SIZE + (WIDTH - MINIMAP_WIDTH),
				tile_y * MINIMAP_TILE_SIZE, color);
			tile_x++;
		}
		tile_y++;
	}
}

static void	draw_minimap_player(t_c *cub, t_minimap minimap,
	float player_tile_x, float player_tile_y)
{
	int			px;
	int			py;
	int			player_bound;
	uint32_t	color;
	t_vector	draw;

	color = 0xFF0000FF;
	player_bound = PLAYER_SIZE / 2;
	draw.x = (int)((player_tile_x - minimap.start_x)
			* MINIMAP_TILE_SIZE) - player_bound / 2 + minimap.offset_x;
	draw.y = (int)((player_tile_y - minimap.start_y)
			* MINIMAP_TILE_SIZE) - player_bound / 2;
	py = 0;
	while (py < player_bound)
	{
		px = 0;
		while (px < player_bound)
		{
			if (draw.x + px >= minimap.offset_x && draw.x + px < WIDTH
				&& draw.y + py >= 0 && draw.y + py < MINIMAP_HEIGHT)
				put_pixel_on_change(cub, draw.x + px, draw.y + py, color);
			px++;
		}
		py++;
	}
}

void	draw_minimap(t_c *cub)
{
	t_minimap	minimap;
	float		player_tile_x;
	float		player_tile_y;

	minimap.offset_x = WIDTH - MINIMAP_WIDTH;
	minimap.tiles_x = MINIMAP_WIDTH / MINIMAP_TILE_SIZE;
	minimap.tiles_y = MINIMAP_HEIGHT / MINIMAP_TILE_SIZE;
	player_tile_x = cub->player.pos.x / TILE_SIZE;
	player_tile_y = cub->player.pos.y / TILE_SIZE;
	minimap.start_x = (int)player_tile_x - minimap.tiles_x / 2;
	minimap.start_y = (int)player_tile_y - minimap.tiles_y / 2;
	if (minimap.start_x < 0)
		minimap.start_x = 0;
	if (minimap.start_y < 0)
		minimap.start_y = 0;
	if (minimap.start_x + minimap.tiles_x > cub->map_width)
		minimap.start_x = cub->map_width - minimap.tiles_x;
	if (minimap.start_y + minimap.tiles_y > cub->map_height)
		minimap.start_y = cub->map_height - minimap.tiles_y;
	draw_minimap_tiles(cub, minimap);
	draw_minimap_rays(cub, minimap);
	draw_minimap_player(cub, minimap,
		player_tile_x, player_tile_y);
}
