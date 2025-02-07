/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:55:10 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/15 16:22:12 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_mlx(t_c *cub, int i)
{
	if (cub->player.player_img)
		mlx_delete_image(cub->mlx, cub->player.player_img);
	if (cub->mlx)
		mlx_delete_image(cub->mlx, cub->img);
	while (cub->map_height)
	{
		cub->map_height--;
		if (cub->map[cub->map_height])
			free(cub->map[cub->map_height]);
	}
	if (cub->map)
		free(cub->map);

	while (cub->texture[i].img)
	{
		if (cub->texture[i].img)
			mlx_delete_image(cub->mlx, cub->texture[i].img);
		i++;
	}
	if (cub->mlx)
		mlx_terminate(cub->mlx);
}

void	er_ex(t_c cub, char *str)
{
	free_mlx(&cub, 0);
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

static void	init_map_and_player(char *file, t_c *cub)
{
	if (!ft_str_end_with(file, ".cub"))
		er_ex(*cub, "Map needs a .cub extension.\n");
	if (!scan_map(file, cub))
		er_ex(*cub, "Invalid map file.\n");
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		er_ex(*cub, "mlx_new_image\n");
	cub->ray_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	draw_map2D(cub);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	create_player(cub, 0, 0);
	mlx_image_to_window(cub->mlx, cub->player.player_img, cub->player.pos.x * TILE_SIZE , cub->player.pos.y * TILE_SIZE);
	mlx_image_to_window(cub->mlx, cub->ray_img, 0, 0);
	cub->player.pos.x = cub->player.player_img->instances[0].x + (PLAYER_SIZE / 2);
	cub->player.pos.y = cub->player.player_img->instances[0].y + (PLAYER_SIZE / 2);
}

void	input_loop(mlx_key_data_t keydata, void* param)
{
	t_c *cub = (t_c*)param;	
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(cub->mlx);	
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) //Move forward
	{
		cub->player.pos.x += cub->player.delta_pos.x;
		cub->player.pos.y += cub->player.delta_pos.y;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS) //Move back
	{
		cub->player.pos.x -= cub->player.delta_pos.x;
		cub->player.pos.y -= cub->player.delta_pos.y;
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS) //Move left
	{
		cub->player.pos.x += sin(cub->player.angle) * 5;
		cub->player.pos.y -= cos(cub->player.angle) * 5;
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS) //Move right
	{
		cub->player.pos.x -= sin(cub->player.angle) * 5;
		cub->player.pos.y += cos(cub->player.angle) * 5;
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) //Rotate right
	{
		cub->player.angle += 0.1;
		if (cub->player.angle > 2 * PI)
			cub->player.angle -= 2 * PI;
		cub->player.delta_pos = (t_vector){cos(cub->player.angle) * 5, sin(cub->player.angle) * 5};
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)	//Rotate left
	{
		cub->player.angle -= 0.1;
		if (cub->player.angle < 0)
			cub->player.angle += 2 * PI;
		cub->player.delta_pos = (t_vector){cos(cub->player.angle) * 5, sin(cub->player.angle) * 5};
	}
	cub->player.player_img->instances[0].x = cub->player.pos.x - (PLAYER_SIZE / 2);
	cub->player.player_img->instances[0].y = cub->player.pos.y - (PLAYER_SIZE / 2);
	raycast(cub);
}


// void	game_loop(void *param)
// {
// 	t_c *cub = (t_c*)param;
// 	//mlx_image_to_window(cub->mlx, cub->img, 0, 0);
// 	//mlx_image_to_window(cub->mlx, cub->player.player_img, cub->player.pos.x * TILE_SIZE, cub->player.pos.y * TILE_SIZE);
// }

int	main(int argc, char **argv)
{
	t_c		cub;

	if (argc != 2)
		return (write(2, "Usage: ./cub3D <map_file.cub>\n", 30), EXIT_FAILURE);
	ft_memset(&cub, 0, sizeof(t_c));
	cub.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!cub.mlx)
		er_ex(cub, "mlx_init");
	init_map_and_player(argv[1], &cub);
	//mlx_loop_hook(cub.mlx, ft_hook, &cub);
	mlx_key_hook(cub.mlx, input_loop, &cub);
	mlx_loop(cub.mlx);
	printf("successfully loaded map\n");  // debug

	free_mlx(&cub, 0);
	write(1, "Game Over.\n", 11);
	return (EXIT_SUCCESS);
}
