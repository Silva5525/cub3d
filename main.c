/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:55:10 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/18 22:45:05 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_mlx(t_c *cub, int i)
{
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
	cub->mini_map = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->mini_map)
		er_ex(*cub, "mlx_new_minimap_image\n");
	cub->ray_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->ray_img)
		er_ex(*cub, "mlx_new_ray_image\n");
	cub->world_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->world_img)
		er_ex(*cub, "mlx_new_world_image\n");

	mlx_image_to_window(cub->mlx, cub->img, 0, 0);	
	mlx_image_to_window(cub->mlx, cub->world_img, 0, 0);	
	mlx_image_to_window(cub->mlx, cub->mini_map, 0, 0);
	draw_floor_and_ceiling(cub);
	draw_map2d(cub, 0, 0, 0);
	create_player(cub, 0, 0);
	mlx_image_to_window(cub->mlx, cub->player.player_img, cub->player.pos.x * TILE_SIZE , cub->player.pos.y * TILE_SIZE);
	mlx_image_to_window(cub->mlx, cub->ray_img, 0, 0);
	cub->player.pos.x = cub->player.player_img->instances[0].x + (PLAYER_SIZE / 2);
	cub->player.pos.y = cub->player.player_img->instances[0].y + (PLAYER_SIZE / 2);
}

void	key_hook(void *param)
{
	t_c *cub = (t_c *)param;
	t_vector delta = {0, 0};

	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(cub->mlx, MLX_KEY_E)) // Rotate right
	{
		cub->player.angle += 0.05;
		if (cub->player.angle > 2 * PI)
			cub->player.angle -= 2 * PI;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT) || mlx_is_key_down(cub->mlx, MLX_KEY_Q)) // Rotate left
	{
		cub->player.angle -= 0.05;
		if (cub->player.angle < 0)
			cub->player.angle += 2 * PI;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W)) // Forward
	{
		delta.x += cos(cub->player.angle) * 4;
		delta.y += sin(cub->player.angle) * 4;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S)) // Backward
	{
		delta.x -= cos(cub->player.angle) * 4;
		delta.y -= sin(cub->player.angle) * 4;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A)) // Left
	{
		delta.x += sin(cub->player.angle) * 4;
		delta.y -= cos(cub->player.angle) * 4;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D)) // Right
	{
		delta.x -= sin(cub->player.angle) * 4;
		delta.y += cos(cub->player.angle) * 4;
	}

	// APPLY MOVEMENT ONLY IF DELTA IS NOT ZERO
	if (delta.x != 0 || delta.y != 0)
	{
		t_vector position = {
			cub->player.pos.x + delta.x,
			cub->player.pos.y + delta.y
		};
		/* if (position.x < 0 || position.y < 0 || 
			position.x >= cub->map_width * TILE_SIZE ||
			position.y >= cub->map_height * TILE_SIZE)
		{
			printf("Out of bounds! Position: (%f, %f)\n", position.x, position.y);
			return;
		} */
		
		// COLLISION CHECK
		if (collision(cub, position.x, position.y))
		{
		    delta.x = 0;
		    delta.y = 0;
			printf("Collision! Stopping movement.\n");
		}
		else
		{
		    cub->player.pos = position;
		    if (cub->player.player_img && cub->player.player_img->instances)
		    {
		        cub->player.player_img->instances[0].x = position.x - (PLAYER_SIZE / 2);
		        cub->player.player_img->instances[0].y = position.y - (PLAYER_SIZE / 2);
		    }
		}
	}
	// RENDER
	clear_img(cub->ray_img);
	clear_img(cub->world_img);
	raycast(cub);
}



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
	mlx_loop_hook(cub.mlx, key_hook, &cub);
	mlx_loop(cub.mlx);
	printf("successfully loaded map\n");  // debug

	free_mlx(&cub, 0);
	write(1, "Game Over.\n", 11);
	return (EXIT_SUCCESS);
}
