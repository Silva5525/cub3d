/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:50:15 by mgering           #+#    #+#             */
/*   Updated: 2025/02/20 15:50:15 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		vertical_hit(t_c *cub, t_hit *hit, t_ray *hit_v, int r);
static void		horizontal_hit(t_c *cub, t_hit *hit, t_ray *hit_h, int r);

void	ray(t_c *cub)
{
	int			r;
	t_hit		hit;
	t_ray		hit_h;
	t_ray		hit_v;

	hit_h.distance_vec = &(float){1000000};
	hit_v.distance_vec = &(float){1000000};
	hit.ra = cub->player.angle - (30 * DEGREE);
	r = 0;
	while (r < WIDTH)
	{
		hit.ra = fmod(hit.ra + 2 * PI, 2 * PI);
		check_horizontal_hit(cub, hit.ra, &hit_h);
		check_vertical_hit(cub, hit.ra, &hit_v);
		if (*(hit_v.distance_vec) < *(hit_h.distance_vec))
			vertical_hit(cub, &hit, &hit_v, r);
		else
			horizontal_hit(cub, &hit, &hit_h, r);
		hit.ra += (60 * DEGREE) / WIDTH;
		r++;
	}
}

static void	vertical_hit(t_c *cub, t_hit *hit, t_ray *hit_v, int r)
{
	hit->vec = hit_v->vec;
	hit->distance = *(hit_v->distance_vec);
	draw_line_dda(cub->ray_img, cub->player.pos, hit->vec, 0x00FF009A);
	hit->distance *= cos(cub->player.angle - hit->ra);
	draw_3d(cub, true, hit, r);
}

static void	horizontal_hit(t_c *cub, t_hit *hit, t_ray *hit_h, int r)
{
	hit->vec = hit_h->vec;
	hit->distance = *(hit_h->distance_vec);
	draw_line_dda(cub->ray_img, cub->player.pos, hit->vec, 0x00FF009A);
	hit->distance *= cos(cub->player.angle - hit->ra);
	draw_3d(cub, false, hit, r);
}

void	calculate_wall_dimensions(float final_dist, t_wall *wall)
{
	if (final_dist > 0.1)
		wall->wall_height = (TILE_SIZE * HEIGHT) / final_dist;
	else
		wall->wall_height = (TILE_SIZE * HEIGHT) / 0.1;
	wall->draw_start = (HEIGHT / 2) - (wall->wall_height / 2);
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = (HEIGHT / 2) + (wall->wall_height / 2);
	if (wall->draw_end >= HEIGHT)
		wall->draw_end = HEIGHT - 1;
}

void	draw_wall_slice(t_c *cub, int x, t_wall *wall)
{
	float		step;
	float		tex_pos;
	int			tex_y;
	int			y;
	uint32_t	color;

	y = wall->draw_start;
	if (wall->wall_height > 1)
		step = (float)wall->texture->height / wall->wall_height;
	else
		step = 1;
	tex_pos = (wall->draw_start - (HEIGHT / 2)
			+ (wall->wall_height / 2)) * step;
	while (y < wall->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= (int)wall->texture->height)
			tex_y = wall->texture->height - 1;
		tex_pos += step;
		color = convert_color(((uint32_t *)wall->texture->pixels)[tex_y
				* wall->texture->width + wall->tex_x]);
		mlx_put_pixel(cub->world_img, x, y, color);
		y++;
	}
}
