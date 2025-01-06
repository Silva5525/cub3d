/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:25:56 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/06 14:53:48 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 512
#define HEIGHT 512
#define SQUARE_SIZE 50

static mlx_image_t* square;

void	ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);

	if (mlx_is_key_down(mlx, MLX_KEY_W))
		square->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		square->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		square->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		square->instances[0].x += 5;
}

int32_t	main(void)
{
	mlx_t	*mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "WASD Movement", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}

	if (!(square = mlx_new_image(mlx, SQUARE_SIZE, SQUARE_SIZE)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}

	for (uint32_t y = 0; y < square->height; ++y)
	{
		for (uint32_t x = 0; x < square->width; ++x)
		{
			mlx_put_pixel(square, x, y, 0xFF0000FF);
		}
	}

	if (mlx_image_to_window(mlx, square, WIDTH / 2 - SQUARE_SIZE / 2
			, HEIGHT / 2 - SQUARE_SIZE / 2) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}

	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
