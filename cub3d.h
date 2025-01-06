/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:31:32 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/06 14:59:39 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <MLX42/MLX42.h>

typedef struct s_texture
{
	mlx_image_t		*img;
	int				width;
	int				height;
}					t_texture;

typedef struct s_vector
{
	double	x;
	double	y;
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

}					t_c;


#endif