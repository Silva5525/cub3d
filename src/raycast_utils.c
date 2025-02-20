/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:50:15 by mgering           #+#    #+#             */
/*   Updated: 2025/02/20 15:50:15 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_until_wall(t_c *cub, t_ray *ray)
{
	int	mx;
	int	my;

	while (true)
	{
		mx = (int)(ray->intersect.x / TILE_SIZE);
		my = (int)(ray->intersect.y / TILE_SIZE);
		if (mx < 0 || my < 0 || mx >= cub->map_width || my >= cub->map_height)
			break ;
		if (cub->map[my][mx] == '1')
		{
			ray->vec.x = ray->intersect.x;
			ray->vec.y = ray->intersect.y;
			*ray->distance_vec = distance(cub->player.pos.x,
					cub->player.pos.y, ray->intersect.x, ray->intersect.y);
			break ;
		}
		ray->intersect.x += ray->step.x;
		ray->intersect.y += ray->step.y;
	}
}

static void	check_up_down(t_c *cub, t_ray *ray, float ra)
{
	float	a_tan;

	a_tan = -1 / tan(ra);
	if (ra > PI)
	{
		ray->intersect.y = (((int)cub->player.pos.y >> 5) << 5) - 0.0001;
		ray->intersect.x = (cub->player.pos.y - ray->intersect.y)
			* a_tan + cub->player.pos.x;
		ray->step.y = -TILE_SIZE;
		ray->step.x = -ray->step.y * a_tan;
	}
	else if (ra < PI)
	{
		ray->intersect.y = (((int)cub->player.pos.y >> 5) << 5) + TILE_SIZE;
		ray->intersect.x = (cub->player.pos.y - ray->intersect.y)
			* a_tan + cub->player.pos.x;
		ray->step.y = TILE_SIZE;
		ray->step.x = -ray->step.y * a_tan;
	}
	else
	{
		ray->intersect.x = cub->player.pos.x;
		ray->intersect.y = cub->player.pos.y;
		return ;
	}
}

static void	check_left_right(t_c *cub, t_ray *ray, float ra)
{
	float	n_tan;

	n_tan = -tan(ra);
	if (ra > (PI / 2) && ra < (3 * PI / 2))
	{
		ray->intersect.x = (((int)cub->player.pos.x >> 5) << 5) - 0.0001;
		ray->intersect.y = (cub->player.pos.x - ray->intersect.x)
			* n_tan + cub->player.pos.y;
		ray->step.x = -TILE_SIZE;
		ray->step.y = -ray->step.x * n_tan;
	}
	else if (ra < (PI / 2) || ra > (3 * PI / 2))
	{
		ray->intersect.x = (((int)cub->player.pos.x >> 5) << 5) + TILE_SIZE;
		ray->intersect.y = (cub->player.pos.x - ray->intersect.x)
			* n_tan + cub->player.pos.y;
		ray->step.x = TILE_SIZE;
		ray->step.y = -ray->step.x * n_tan;
	}
	else
	{
		ray->intersect.x = cub->player.pos.x;
		ray->intersect.y = cub->player.pos.y;
		return ;
	}
}

void	check_horizontal_hit(t_c *cub, float ra, t_ray *ray)
{
	*ray->distance_vec = 1000000;
	ray->vec.x = cub->player.pos.x;
	ray->vec.y = cub->player.pos.y;
	check_up_down(cub, ray, ra);
	check_until_wall(cub, ray);
}

void	check_vertical_hit(t_c *cub, float ra, t_ray *ray)
{
	*ray->distance_vec = 1000000;
	ray->vec.x = cub->player.pos.x;
	ray->vec.y = cub->player.pos.y;
	check_left_right(cub, ray, ra);
	check_until_wall(cub, ray);
}
