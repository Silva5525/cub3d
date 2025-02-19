/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:31:32 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/19 12:05:08 by wdegraf          ###   ########.fr       */
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

# define WIDTH 2048
# define HEIGHT 1024
# define TILE_SIZE 32
# define PLAYER_SIZE 16
# define PI 3.141592
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05
# define DEGREE 0.0174533

typedef struct s_texture
{
	mlx_image_t		*img;
	int				width;
	int				height;
}					t_texture;

typedef struct s_vector
{
	float			x;
	float			y;
}					t_vector;

typedef struct s_player
{
	mlx_image_t		*player_img;
	t_vector		pos;
	t_vector		delta_pos;
	t_vector		dir;
	float			angle;
	t_vector		plane;
}					t_player;

typedef struct s_cub3d
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*ray_img;
	mlx_image_t		*world_img;
	mlx_image_t		*mini_map;
	char			**map;
	int				map_width;
	int				map_height;
	t_texture		texture[4];
	int				roof;
	int				floor;
	t_player		player;
}					t_c;


//----------------------main.c------------------------------
int				main(int argc, char **argv);

//----------------------keys.c------------------------------
void			key_hook(void *param);

//----------------------create_player.c---------------------
float			init_angle(char view);
void			draw_player(t_c *cub);
void			create_player(t_c *cub, int x, int y);

//----------------------draw_map.c--------------------------
void			draw_map2d(t_c *cub, int x, int y, int ty);
void			draw_floor_and_ceiling(t_c *cub);

//----------------------draw_utils.c------------------------
void			clear_img(mlx_image_t *img);

//----------------------err_handling.c----------------------
void			delete_if(t_c *cub);
void			free_mlx(t_c *cub, int i);
void			er_ex(t_c cub, char *str);

//----------------------parse_line.c------------------------
bool			parse_line(char *trim_line, t_c *cub, mlx_texture_t *texture, char *path);

//----------------------parse_map.c-------------------------
bool			scan_map(char *file, t_c *cub);

//----------------------raycast.c---------------------------
void			raycast(t_c *cub);
float			distance(float x1, float y1, float x2, float y2);
void			draw_line_dda(mlx_image_t *ray_img, float x0, float y0, float x1, float y1, uint32_t color);
bool			collision(t_c *cub, float x, float y);
bool			is_wall(t_c *cub, float x, float y);
void			draw_3d(t_c *cub, int x, float final_dist, bool vertical_hit, float hit_x, float hit_y);

//----------------------valid_map.c-------------------------
bool			map_err(char *line, int fd);
bool			valid_map(t_c *cub, int p_count, int x, int y);

#endif