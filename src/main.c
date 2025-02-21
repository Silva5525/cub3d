/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:55:10 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/19 12:05:42 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_map_and_player2(t_c *cub)
{
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	mlx_image_to_window(cub->mlx, cub->world_img, 0, 0);
	//mlx_image_to_window(cub->mlx, cub->mini_map, 0, 0);
	draw_floor_and_ceiling(cub);
	//draw_map2d(cub, 0, 0, 0);
	create_player(cub, 0, 0);
	mlx_image_to_window(cub->mlx, cub->player.player_img, cub->player.pos.x
		* TILE_SIZE, cub->player.pos.y * TILE_SIZE);
	//mlx_image_to_window(cub->mlx, cub->ray_img, 0, 0);
	cub->player.pos.x = cub->player.player_img->instances[0].x
		+ (PLAYER_SIZE / 2);
	cub->player.pos.y = cub->player.player_img->instances[0].y
		+ (PLAYER_SIZE / 2);
}

static void	init_map_and_player(char *file, t_c *cub)
{
	if (!ft_str_end_with(file, ".cub"))
		er_ex(cub, "Map needs a .cub extension.\n");
	if (!scan_map(file, cub))
		er_ex(cub, "Invalid map file.\n");
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		er_ex(cub, "mlx_new_image\n");
	// cub->mini_map = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	// if (!cub->mini_map)
	// 	er_ex(cub, "mlx_new_minimap_image\n");
	//cub->ray_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	//if (!cub->ray_img)
	//	er_ex(cub, "mlx_new_ray_image\n");
	cub->world_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->world_img)
		er_ex(cub, "mlx_new_world_image\n");
	init_map_and_player2(cub);
}

int	main(int argc, char **argv)
{
	t_c		cub;

	if (argc != 2)
		return (write(2, "Usage: ./cub3D <map_file.cub>\n", 30), EXIT_FAILURE);
	ft_memset(&cub, 0, sizeof(t_c));
	cub.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!cub.mlx)
		er_ex(&cub, "mlx_init");
	init_map_and_player(argv[1], &cub);
	mlx_loop_hook(cub.mlx, key_hook, &cub);
	mlx_loop(cub.mlx);
	free_mlx(&cub);
	write(1, "Game Over.\n", 11);
	return (EXIT_SUCCESS);
}
