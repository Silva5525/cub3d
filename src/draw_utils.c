/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:05:12 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/18 22:05:15 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clear_img(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(uint32_t));
}
