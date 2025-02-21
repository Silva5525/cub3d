/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:01:59 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/19 12:02:14 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	delete_if(t_c *cub)
{
	if (!cub || !cub->mlx)
		return ;
	if (cub->player.player_img)
		mlx_delete_image(cub->mlx, cub->player.player_img);
	if (cub->world_img)
		mlx_delete_image(cub->mlx, cub->world_img);
	if (cub->ray_img)
		mlx_delete_image(cub->mlx, cub->ray_img);
	if (cub->mini_map)
		mlx_delete_image(cub->mlx, cub->mini_map);
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
	if (cub->mlx)
	{
		printf("Terminating MLX.../n");
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
