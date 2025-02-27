/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:50:15 by mgering           #+#    #+#             */
/*   Updated: 2025/02/27 17:17:24 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	select_texture(t_c *cub, mlx_image_t **texture,
	t_vector vec, bool hit)
{
	if (hit)
	{
		if (vec.x < cub->player.pos.x)
			*texture = cub->texture[2].img;
		else
			*texture = cub->texture[3].img;
	}
	else
	{
		if (vec.y < cub->player.pos.y)
			*texture = cub->texture[0].img;
		else
			*texture = cub->texture[1].img;
	}
}

uint32_t	select_texture_x(t_c *cub, mlx_image_t *texture,
	t_vector vec, bool hit)
{
	uint32_t	tex_x;
	float		fx;
	float		fy;

	fx = fmod(vec.x, TILE_SIZE);
	fy = fmod(vec.y, TILE_SIZE);
	if (hit)
		tex_x = (int)(fy / TILE_SIZE * texture->width);
	else
		tex_x = (int)(fx / TILE_SIZE * texture->width);
	if ((hit && vec.x < cub->player.pos.x)
		|| (!hit && vec.y > cub->player.pos.y))
		tex_x = texture->width - tex_x - 1;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

static uint32_t	get_texture_color(t_wall *wall, uint32_t *tex_pixels,
	float tex_pos)
{
	int	tex_y;

	tex_y = (int)tex_pos;
	if (tex_y >= (int)wall->texture->height)
		tex_y = wall->texture->height - 1;
	return (convert_color(tex_pixels[tex_y
				* wall->texture->width + wall->tex_x]));
}

void	draw_wall_slice(t_c *cub, int x, t_wall *wall)
{
	int			y;
	uint32_t	color;

	y = -1;
	while (++y < wall->draw_start)
	{
		color = cub->roof;
		if (cub->last_frame_pixel[y * WIDTH + x] != color)
		{
			mlx_put_pixel(cub->img, x, y, color);
			cub->last_frame_pixel[y * WIDTH + x] = color;
		}
	}
	if (wall->texture)
		draw_wall_tex(cub, wall, x, &y);
	while (++y < HEIGHT)
	{
		color = cub->floor;
		if (cub->last_frame_pixel[y * WIDTH + x] != color)
		{
			mlx_put_pixel(cub->img, x, y, color);
			cub->last_frame_pixel[y * WIDTH + x] = color;
		}
	}
}

void	draw_wall_tex(t_c *cub, t_wall *wall, int x, int *y)
{
	float		tex_pos;
	float		step;
	uint32_t	color;
	uint32_t	*tex_pixels;

	tex_pixels = (uint32_t *)wall->texture->pixels;
	if (!tex_pixels)
		return ;
	if (wall->wall_height > 1)
		step = (float)wall->texture->height / wall->wall_height;
	else
		step = 1;
	tex_pos = (wall->draw_start - (HEIGHT / 2)
			+ (wall->wall_height / 2)) * step;
	while (*y < wall->draw_end)
	{
		color = get_texture_color(wall, tex_pixels, tex_pos);
		if (cub->last_frame_pixel[*y * WIDTH + x] != color)
		{
			mlx_put_pixel(cub->img, x, *y, color);
			cub->last_frame_pixel[*y * WIDTH + x] = color;
		}
		(*y)++;
		tex_pos += step;
	}
}
