/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:55:10 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/06 19:28:44 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_file(char *file, t_c *cub)
{
	if (!ft_str_end_with(file, ".cub"))
		er_ex(*cub, "Map needs a .cub extension.\n");
	if (!scan_map(file, cub))
		er_ex(*cub, "Invalid map file.\n");
}

void	er_ex(t_c cub, char *str)
{
	if (cub.mlx)
		mlx_close_window(cub.mlx);
	write(2, &str, ft_strlen(str));
	exit(EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}
