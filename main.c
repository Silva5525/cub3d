/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:55:10 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/10 16:55:19 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	er_ex(t_c cub, char *str)
{
	if (cub.mlx)
		mlx_close_window(cub.mlx);
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

static void	check_file(char *file, t_c *cub)
{
	if (!ft_str_end_with(file, ".cub"))
		er_ex(*cub, "Map needs a .cub extension.\n");
	if (!scan_map(file, cub))
		er_ex(*cub, "Invalid map file.\n");
}

void	free_mlx(t_c *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->texture[i].img)
			mlx_delete_image(cub->mlx, cub->texture[i].img);
		i++;
	}
	if (cub->mlx)
		mlx_terminate(cub->mlx);
}

int	main(int argc, char **argv)
{
	t_c		cub;

	if (argc != 2)
	{
		puts("Usage: ./cub3D <map_file.cub>");
		return (EXIT_FAILURE);
	}
	ft_memset(&cub, 0, sizeof(t_c));
	cub.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!cub.mlx)
		er_ex(cub, "mlx_init");
	check_file(argv[1], &cub);
	printf("successfully loaded map\n");  // debug
	free_mlx(&cub);
	return (EXIT_SUCCESS);
}
