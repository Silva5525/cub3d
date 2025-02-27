/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:01:59 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/27 17:16:44 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	delete_if(t_c *cub)
{
	if (!cub || !cub->mlx)
		return ;
	if (cub->img)
		mlx_delete_image(cub->mlx, cub->img);
}

void	free_mlx(t_c *cub)
{
	delete_if(cub);
	while (cub->map_height > 0)
	{
		cub->map_height--;
		if (cub->map[cub->map_height])
			free(cub->map[cub->map_height]);
	}
	if (cub->map)
		free(cub->map);
	if (cub->last_frame_pixel)
		free(cub->last_frame_pixel);
	if (cub->mlx)
	{
		ft_printf("Terminating MLX...\n");
		mlx_terminate(cub->mlx);
		cub->mlx = NULL;
	}
}

void	er_ex(t_c *cub, char *str)
{
	free_mlx(cub);
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}
