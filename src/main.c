/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:55:10 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/28 18:07:09 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_map_and_player2(t_c *cub)
{
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	init_player(cub, 0, 0);
	cub->player.pos.x = cub->player.pos.x * TILE_SIZE
		+ (PLAYER_SIZE / 2);
	cub->player.pos.y = cub->player.pos.y * TILE_SIZE
		+ (PLAYER_SIZE / 2);
}

static void	init_map_and_player(char *file, t_c *cub)
{
	cub->roof = -1;
	cub->floor = -1;
	cub->compass = -1;
	if (!ft_str_end_with(file, ".cub"))
		er_ex(cub, "Map needs a .cub extension.\n");
	if (!scan_map(file, cub))
		er_ex(cub, "Invalid map file.\n");
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		er_ex(cub, "mlx_new_image\n");
	cub->last_frame_pixel = malloc(WIDTH * HEIGHT * sizeof(uint32_t));
	if (!cub->last_frame_pixel)
		er_ex(cub, "Failed to allocate last_frame_pixels\n");
	memset(cub->last_frame_pixel, 0, WIDTH * HEIGHT * sizeof(uint32_t));
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
