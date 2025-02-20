/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:05:12 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/18 22:05:15 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_img(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(uint32_t));
}

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	draw_line_dda(mlx_image_t *ray_img, t_vector start_vec,
	t_vector end_vec, uint32_t color)
{
	int		i;
	float	dx;
	float	dy;
	float	steps;

	i = 0;
	dx = end_vec.x - start_vec.x;
	dy = end_vec.y - start_vec.y;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	while (i <= steps)
	{
		mlx_put_pixel(ray_img, (int)round(start_vec.x),
			(int)round(start_vec.y), color);
		start_vec.x += dx / steps;
		start_vec.y += dy / steps;
		i++;
	}
}

uint32_t	convert_color(uint32_t color)
{
	uint8_t	*channels;

	channels = (uint8_t *)&color;
	return ((uint32_t)channels[2] << 8
		| (uint32_t)channels[1] << 16
		| (uint32_t)channels[0] << 24
		| (uint32_t)channels[3]);
}
