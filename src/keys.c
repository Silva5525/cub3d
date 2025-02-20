/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:57:45 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/19 12:14:48 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	key_position(t_c *cub, t_vector delta)
{
	t_vector	position;

	if (delta.x != 0 || delta.y != 0)
	{
		position
			= (t_vector){
			cub->player.pos.x + delta.x,
			cub->player.pos.y + delta.y
		};
		if (collision(cub, position.x, position.y))
			delta = (t_vector){0, 0};
		else
		{
			cub->player.pos = position;
			if (cub->player.player_img && cub->player.player_img->instances)
			{
				cub->player.player_img->instances[0].x
					= position.x - (PLAYER_SIZE / 2);
				cub->player.player_img->instances[0].y
					= position.y - (PLAYER_SIZE / 2);
			}
		}
	}
}

static void	key_rotations(t_c *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(cub->mlx, MLX_KEY_E))
	{
		cub->player.angle += 0.05;
		if (cub->player.angle > 2 * PI)
			cub->player.angle -= 2 * PI;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(cub->mlx, MLX_KEY_Q))
	{
		cub->player.angle -= 0.05;
		if (cub->player.angle < 0)
			cub->player.angle += 2 * PI;
	}
}

static void	key_movements(t_c *cub, t_vector *delta)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		delta->x += cos(cub->player.angle) * 4;
		delta->y += sin(cub->player.angle) * 4;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		delta->x -= cos(cub->player.angle) * 4;
		delta->y -= sin(cub->player.angle) * 4;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		delta->x += sin(cub->player.angle) * 4;
		delta->y -= cos(cub->player.angle) * 4;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		delta->x -= sin(cub->player.angle) * 4;
		delta->y += cos(cub->player.angle) * 4;
	}
}

void	key_hook(void *param)
{
	t_c			*cub;
	t_vector	delta;

	cub = (t_c *)param;
	delta = (t_vector){0, 0};
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	key_rotations(cub);
	key_movements(cub, &delta);
	key_position(cub, delta);
	clear_img(cub->ray_img);
	clear_img(cub->world_img);
	ray(cub);
}
