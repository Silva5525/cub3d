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
	if (cub->mlx)
		mlx_close_window(cub->mlx);
	while (cub->map_height)
	{
		cub->map_height--;
		if (cub->map[cub->map_height])
			free(cub->map[cub->map_height]);
		cub->map[cub->map_height] = NULL;
	}
	if (cub->map)
	{
		free(cub->map);
		cub->map = NULL;
	}
	while (cub->texture[i].img)
	{
		if (cub->texture[i].img)
			mlx_delete_image(cub->mlx, cub->texture[i].img);
		cub->texture[i].img = NULL;
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
	create_player(cub, 0, 0);
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
	printf("successfully loaded map\n");  // debug
	free_mlx(&cub, 0);
	write(1, "Game Over.\n", 11);
	return (EXIT_SUCCESS);
}
