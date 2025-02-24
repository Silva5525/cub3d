/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_drawing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:58:17 by mgering           #+#    #+#             */
/*   Updated: 2025/02/20 20:02:41 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_tile(t_c *cub, int dest_x, int dest_y, uint32_t color)
{
	int	px;
	int	py;
	int	index;

	py = 0;
	while (py < MINIMAP_TILE_SIZE)
	{
		px = 0;
		while (px < MINIMAP_TILE_SIZE)
		{
			index = (dest_y + py) * WIDTH + (dest_x + px);
			if (cub->last_frame_pixel[index] != color)
			{
				mlx_put_pixel(cub->img, dest_x + px, dest_y + py, color);
				cub->last_frame_pixel[index] = color;
			}
			px++;
		}
		py++;
	}
}

static char	get_map_char(t_c *cub, int x, int y)
{
	if (y < 0 || y >= cub->map_height || !cub->map[y])
		return ('1');
	if (x < 0 || x >= (int)ft_strlen(cub->map[y]))
		return ('1');
	return (cub->map[y][x]);
}

static void	draw_minimap_tiles(t_c *cub, int start_tile_x, int start_tile_y,
	int view_tile_w, int view_tile_h, int minimap_offset_x)
{
	int			tile_x;
	int			tile_y;
	int			map_x;
	int			map_y;
	uint32_t	color;

	tile_y = 0;
	while (tile_y < view_tile_h)
	{
		tile_x = 0;
		while (tile_x < view_tile_w)
		{
			map_x = start_tile_x + tile_x;
			map_y = start_tile_y + tile_y;
			if (get_map_char(cub, map_x, map_y) == '1'
				|| get_map_char(cub, map_x, map_y) == ' ')
				color = 0x0000009E;
			else
				color = 0x80809E9E;
			draw_tile(cub, tile_x * MINIMAP_TILE_SIZE + minimap_offset_x,
				tile_y * MINIMAP_TILE_SIZE, color);
			tile_x++;
		}
		tile_y++;
	}
}

static void	draw_minimap_player(t_c *cub, int start_tile_x, int start_tile_y,
	float player_tile_x, float player_tile_y, int minimap_offset_x)
{
	int			p_size;
	int			px;
	int			py;
	int			draw_x;
	int			draw_y;
	int			index;
	uint32_t	color;

	color = 0xFF0000FF;
	p_size = MINIMAP_TILE_SIZE / 2;
	draw_x = (int)((player_tile_x - start_tile_x)
			* MINIMAP_TILE_SIZE) - p_size / 2 + minimap_offset_x;
	draw_y = (int)((player_tile_y - start_tile_y)
			* MINIMAP_TILE_SIZE) - p_size / 2;
	py = 0;
	while (py < p_size)
	{
		px = 0;
		while (px < p_size)
		{
			if (draw_x + px >= minimap_offset_x && draw_x + px < WIDTH
				&& draw_y + py >= 0 && draw_y + py < MINIMAP_HEIGHT)
			{
				index = (draw_y + py) * WIDTH + (draw_x + px);
				if (cub->last_frame_pixel[index] != color)
				{
					mlx_put_pixel(cub->img, draw_x + px, draw_y + py, color);
					cub->last_frame_pixel[index] = color;
				}
			}
			px++;
		}
		py++;
	}
}

void	draw_minimap(t_c *cub)
{
	float	player_tile_x;
	float	player_tile_y;
	int		view_tile_w;
	int		view_tile_h;
	int		start_tile_x;
	int		start_tile_y;
	int		minimap_offset_x;

	minimap_offset_x = WIDTH - MINIMAP_WIDTH;
	view_tile_w = MINIMAP_WIDTH / MINIMAP_TILE_SIZE;
	view_tile_h = MINIMAP_HEIGHT / MINIMAP_TILE_SIZE;
	player_tile_x = cub->player.pos.x / TILE_SIZE;
	player_tile_y = cub->player.pos.y / TILE_SIZE;
	start_tile_x = (int)player_tile_x - view_tile_w / 2;
	start_tile_y = (int)player_tile_y - view_tile_h / 2;
	if (start_tile_x < 0)
		start_tile_x = 0;
	if (start_tile_y < 0)
		start_tile_y = 0;
	if (start_tile_x + view_tile_w > cub->map_width)
		start_tile_x = cub->map_width - view_tile_w;
	if (start_tile_y + view_tile_h > cub->map_height)
		start_tile_y = cub->map_height - view_tile_h;
	draw_minimap_tiles(cub, start_tile_x, start_tile_y,
		view_tile_w, view_tile_h, minimap_offset_x);
	draw_minimap_rays(cub, start_tile_x, start_tile_y, minimap_offset_x);
	draw_minimap_player(cub, start_tile_x, start_tile_y,
		player_tile_x, player_tile_y, minimap_offset_x);
}

static t_vector	intersect_ray_with_rect(t_vector start, t_vector end,
	int rect_x, int rect_y, int rect_w, int rect_h)
{
t_vector	dir;
float		t;
float		t_candidate;
t_vector	intersect;

dir.x = end.x - start.x;
dir.y = end.y - start.y;
t = 1.0f;  // default: the computed endpoint is at t = 1
// Check left boundary
if (dir.x != 0)
{
t_candidate = ((float)rect_x - start.x) / dir.x;
if (t_candidate >= 0 && t_candidate < t)
t = t_candidate;
}
// Check right boundary
if (dir.x != 0)
{
t_candidate = ((float)(rect_x + rect_w) - start.x) / dir.x;
if (t_candidate >= 0 && t_candidate < t)
t = t_candidate;
}
// Check top boundary
if (dir.y != 0)
{
t_candidate = ((float)rect_y - start.y) / dir.y;
if (t_candidate >= 0 && t_candidate < t)
t = t_candidate;
}
// Check bottom boundary
if (dir.y != 0)
{
t_candidate = ((float)(rect_y + rect_h) - start.y) / dir.y;
if (t_candidate >= 0 && t_candidate < t)
t = t_candidate;
}
intersect.x = start.x + dir.x * t;
intersect.y = start.y + dir.y * t;
return (intersect);
}

void	draw_minimap_rays(t_c *cub, int start_tile_x,
	int start_tile_y, int minimap_offset_x)
{
	int			r;
	t_hit		hit;
	t_ray		hit_h;
	t_ray		hit_v;
	t_vector	minimap_start;
	t_vector	minimap_end;
	
	hit.ra = cub->player.angle - (30 * DEGREE);
	r = 0;
	minimap_start.x = (cub->player.pos.x / TILE_SIZE - start_tile_x)
		* MINIMAP_TILE_SIZE + minimap_offset_x;
	minimap_start.y = (cub->player.pos.y / TILE_SIZE - start_tile_y)
		* MINIMAP_TILE_SIZE;
	while (r < WIDTH)
	{
		float distance_h = 1000000;
		float distance_v = 1000000;
		hit_h.distance_vec = &distance_h;
		hit_v.distance_vec = &distance_v;
		hit.ra = fmod(hit.ra + 2 * PI, 2 * PI);
		check_horizontal_hit(cub, hit.ra, &hit_h);
		check_vertical_hit(cub, hit.ra, &hit_v);
		if (*(hit_v.distance_vec) < *(hit_h.distance_vec))
		{
			minimap_end.x = (hit_v.vec.x / TILE_SIZE - start_tile_x)
				* MINIMAP_TILE_SIZE + minimap_offset_x;
			minimap_end.y = (hit_v.vec.y / TILE_SIZE - start_tile_y)
				* MINIMAP_TILE_SIZE;
		}
		else
		{
			minimap_end.x = (hit_h.vec.x / TILE_SIZE - start_tile_x)
				* MINIMAP_TILE_SIZE + minimap_offset_x;
			minimap_end.y = (hit_h.vec.y / TILE_SIZE - start_tile_y)
				* MINIMAP_TILE_SIZE;
		}

		// If the computed endpoint is outside the minimap, find the intersection.
		if (minimap_end.x < minimap_offset_x ||
			minimap_end.x > minimap_offset_x + MINIMAP_WIDTH ||
			minimap_end.y < 0 ||
			minimap_end.y > MINIMAP_HEIGHT)
		{
			minimap_end = intersect_ray_with_rect(minimap_start, minimap_end,
					minimap_offset_x, 0, MINIMAP_WIDTH, MINIMAP_HEIGHT);
		}
		draw_line_dda(cub->img, minimap_start, minimap_end, 0x00FF009A);
		hit.ra += (60 * DEGREE) / WIDTH;
		r++;
	}
}
