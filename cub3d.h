/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:31:32 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/24 11:53:06 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft/libft.h>

# include <MLX42/MLX42.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

# define WIDTH 512
# define HEIGHT 512

typedef struct s_texture
{
	mlx_image_t		*img;
	int				width;
	int				height;
}					t_texture;

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_char
{
	t_vector		pos;
	t_vector		dir;
	t_vector		plane;
}					t_char;

typedef struct s_cub3d
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	char			**map;
	int				map_width;
	int				map_height;
	t_texture		texture[4];
	int				roof;
	int				floor;
	t_char			player;
}					t_c;

void	er_ex(t_c cub, char *str);
bool	scan_map(char *file, t_c *cub);
bool	parse_line(char *trim_line, t_c *cub, mlx_texture_t *texture,
			char *path);
bool	valid_map(t_c *cub, int p_count, int x, int y);
void	create_player(t_c *cub, int x, int y);
bool	map_err(char *line, int fd);

#endif