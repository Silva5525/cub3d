#include "cub3d.h"

void	select_texture(t_c *cub, mlx_image_t **texture,
	t_vector vec, bool hit)
{
	if (hit)
	{
		if (vec.x < cub->player.pos.x)
			*texture = cub->texture[2].img;
		else
			*texture = cub->texture[3].img;
	}
	else
	{
		if (vec.y < cub->player.pos.y)
			*texture = cub->texture[0].img;
		else
			*texture = cub->texture[1].img;
	}
}

uint32_t	select_texture_x(mlx_image_t *texture, t_vector vec, bool hit)
{
	uint32_t	tex_x;
	float		fx;
	float		fy;

	fx = fmod(vec.x, TILE_SIZE);
	fy = fmod(vec.y, TILE_SIZE);
	if (hit)
		tex_x = (int)(fy / TILE_SIZE * texture->width);
	else
		tex_x = (int)(fx / TILE_SIZE * texture->width);
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}
