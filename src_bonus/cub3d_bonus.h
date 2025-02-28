/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:31:32 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/28 18:25:36 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <libft/libft.h>
# include <MLX42/MLX42.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

# define WIDTH 2048
# define HEIGHT 1024
# define TILE_SIZE 32
# define MINIMAP_WIDTH 512
# define MINIMAP_HEIGHT 256
# define MINIMAP_TILE_SIZE 16
# define PLAYER_SIZE 16
# define PI 3.141592
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05
# define DEGREE 0.0174533

typedef struct s_minimap
{
	int			offset_x;
	int			tiles_x;
	int			tiles_y;
	int			start_x;
	int			start_y;
}				t_minimap;

typedef struct s_vector
{
	float		x;
	float		y;
}				t_vector;

typedef struct s_hit
{
	t_vector	vec;
	float		distance;
	float		ra;
}				t_hit;

typedef struct s_ray
{
	t_vector	intersect;
	t_vector	step;
	t_vector	vec;
	float		*distance_vec;
}				t_ray;

typedef struct s_miniray
{
	t_vector	minimap_start;
	t_vector	minimap_end;
	t_hit		hit;
	t_ray		hit_h;
	t_ray		hit_v;
}				t_miniray;

typedef struct s_wall
{
	float		draw_start;
	float		draw_end;
	float		wall_height;
	mlx_image_t	*texture;
	uint32_t	tex_x;
}				t_wall;

typedef struct s_texture
{
	mlx_image_t		*img;
	int				width;
	int				height;
}					t_texture;

typedef struct s_player
{
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
	t_texture		texture[4];
	t_player		player;
	char			**map;
	int				map_width;
	int				map_height;
	int				roof;
	int				floor;
	uint32_t		*last_frame_pixel;
	float			last_angle;
	int				compass;
}					t_c;

//----------------------main.c------------------------------
int			main(int argc, char **argv);

//----------------------keys.c------------------------------
void		key_hook(void *param);

//----------------------init_player.c-----------------------
float		init_angle(char view);
void		init_player(t_c *cub, int x, int y);

//----------------------draw_map.c--------------------------
void		draw_floor_and_ceiling(t_c *cub);
void		draw_3d(t_c *cub, bool vertical_hit, t_hit *hit, int r);
void		pad_map_lines(t_c *cub);

//----------------------draw_utils.c------------------------
void		clear_img(mlx_image_t *img);
float		distance(float x1, float y1, float x2, float y2);
uint32_t	convert_color(uint32_t color);
void		draw_line_dda(mlx_image_t *ray_img, t_vector start_vec,
				t_vector end_vec, uint32_t color);

//----------------------texture_utils.c---------------------
void		select_texture(t_c *cub, mlx_image_t **texture,
				t_vector vec, bool hit);
uint32_t	select_texture_x(t_c *cub, mlx_image_t *texture,
				t_vector vec, bool hit);
void		draw_wall_slice(t_c *cub, int x, t_wall *wall);
void		draw_wall_tex(t_c *cub, t_wall *wall, int x, int *y);

//----------------------err_handling.c----------------------
void		delete_if(t_c *cub);
void		free_mlx(t_c *cub);
void		er_ex(t_c *cub, char *str);

//----------------------parse_line.c------------------------
bool		parse_line(char *trim_line, t_c *cub,
				mlx_texture_t *texture, char *path);

//----------------------parse_map.c-------------------------
bool		scan_map(char *file, t_c *cub);

//----------------------raycast.c---------------------------
void		ray(t_c *cub);
void		calculate_wall_dimensions(float final_dist, t_wall *wall);

//----------------------raycast_utils.c---------------------
void		check_horizontal_hit(t_c *cub, float ra, t_ray *ray);
void		check_vertical_hit(t_c *cub, float ra, t_ray *ray);

//----------------------collision_detection.c---------------
bool		collision(t_c *cub, float x, float y);
bool		is_wall(t_c *cub, float x, float y);

//----------------------valid_map.c-------------------------
bool		map_err(char *line, int fd);
bool		valid_map(t_c *cub, int p_count, int x, int y);

//----------------------mini_map.c--------------------------
void		draw_minimap(t_c *cub);

//----------------------mini_map_utils.c---------------------
char		get_map_char(t_c *cub, int x, int y);
void		put_pixel_on_change(t_c *cub, int x, int y, uint32_t color);

//----------------------mini_map_ray.c-----------------------
void		draw_minimap_rays(t_c *cub, t_minimap minimap);

#endif