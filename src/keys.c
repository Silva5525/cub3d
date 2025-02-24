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

static void	try_move(t_c *cub, t_vector delta)
{
	t_vector	pos;
	t_vector	new_pos;

	pos = cub->player.pos;
	new_pos = (t_vector){pos.x + delta.x, pos.y + delta.y};
	if (!collision(cub, new_pos.x, new_pos.y))
	{
		cub->player.pos = new_pos;
		return ;
	}
	new_pos = (t_vector){pos.x + delta.x, pos.y};
	if (!collision(cub, new_pos.x, new_pos.y))
	{
		cub->player.pos = new_pos;
		return ;
	}
	new_pos = (t_vector){pos.x, pos.y + delta.y};
	if (!collision(cub, new_pos.x, new_pos.y))
		cub->player.pos = new_pos;
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
	if (delta.x != 0 || delta.y != 0 || cub->player.angle != cub->last_angle)
	{
		try_move(cub, delta);
		cub->last_angle = cub->player.angle;
		ray(cub);
	}
}
