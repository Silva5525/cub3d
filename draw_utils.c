#include "cub3d.h"

void	clear_img(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(uint32_t));
}