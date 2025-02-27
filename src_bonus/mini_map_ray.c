/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:22:48 by mgering           #+#    #+#             */
/*   Updated: 2025/02/27 17:25:11 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static float	set_t(float t, float t_temp)
{
	if (t_temp >= 0 && t_temp < t)
		t = t_temp;
	return (t);
}

static t_vector	intersect_ray_with_rect(t_miniray *ray, int rect_x)
{
	float		t;
	float		t_temp;
	t_vector	dir;
	t_vector	intersect;

	dir.x = ray->minimap_end.x - ray->minimap_start.x;
	dir.y = ray->minimap_end.y - ray->minimap_start.y;
	t = 1.0f;
	if (dir.x != 0)
	{
		t_temp = (rect_x - ray->minimap_start.x) / dir.x;
		set_t(t, t_temp);
		t_temp = ((rect_x + MINIMAP_WIDTH) - ray->minimap_start.x) / dir.x;
		set_t(t, t_temp);
	}
	if (dir.y != 0)
	{
		t_temp = (rect_x - ray->minimap_start.y) / dir.y;
		t = set_t(t, t_temp);
		t_temp = ((rect_x + MINIMAP_HEIGHT) - ray->minimap_start.y) / dir.y;
		t = set_t(t, t_temp);
	}
	intersect.x = ray->minimap_start.x + dir.x * t;
	intersect.y = ray->minimap_start.y + dir.y * t;
	return (intersect);
}

static void	set_end_vec(t_minimap minimap, t_miniray *ray)
{
	if (*(ray->hit_v.distance_vec) < *(ray->hit_h.distance_vec))
	{
		ray->minimap_end.x = (ray->hit_v.vec.x / TILE_SIZE - minimap.start_x)
			* MINIMAP_TILE_SIZE + minimap.offset_x;
		ray->minimap_end.y = (ray->hit_v.vec.y / TILE_SIZE - minimap.start_y)
			* MINIMAP_TILE_SIZE;
	}
	else
	{
		ray->minimap_end.x = (ray->hit_h.vec.x / TILE_SIZE - minimap.start_x)
			* MINIMAP_TILE_SIZE + minimap.offset_x;
		ray->minimap_end.y = (ray->hit_h.vec.y / TILE_SIZE - minimap.start_y)
			* MINIMAP_TILE_SIZE;
	}
	if (ray->minimap_end.x < minimap.offset_x
		|| ray->minimap_end.x > minimap.offset_x + MINIMAP_WIDTH
		|| ray->minimap_end.y < 0
		|| ray->minimap_end.y > MINIMAP_HEIGHT)
	{
		ray->minimap_end = intersect_ray_with_rect(ray, minimap.offset_x);
	}
}

void	draw_minimap_rays(t_c *cub, t_minimap minimap)
{
	int			r;
	t_miniray	ray;

	r = 0;
	ray.hit.ra = cub->player.angle - (30 * DEGREE);
	ray.minimap_start.x = (cub->player.pos.x / TILE_SIZE - minimap.start_x)
		* MINIMAP_TILE_SIZE + minimap.offset_x;
	ray.minimap_start.y = (cub->player.pos.y / TILE_SIZE - minimap.start_y)
		* MINIMAP_TILE_SIZE;
	while (r < WIDTH)
	{
		ray.hit_h.distance_vec = &(float){1000000};
		ray.hit_v.distance_vec = &(float){1000000};
		ray.hit.ra = fmod(ray.hit.ra + 2 * PI, 2 * PI);
		check_horizontal_hit(cub, ray.hit.ra, &ray.hit_h);
		check_vertical_hit(cub, ray.hit.ra, &ray.hit_v);
		set_end_vec(minimap, &ray);
		draw_line_dda(cub->img, ray.minimap_start, ray.minimap_end, 0x00FF009A);
		ray.hit.ra += (60 * DEGREE) / WIDTH;
		r++;
	}
}
