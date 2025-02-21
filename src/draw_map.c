/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:06:15 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/18 22:36:41 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d(t_c *cub, bool vertical_hit, t_hit *hit, int r)
{
	t_wall	wall;

	wall.texture = NULL;
	calculate_wall_dimensions(hit->distance, &wall);
	select_texture(cub, &wall.texture, hit->vec, vertical_hit);
	wall.tex_x = select_texture_x(cub, wall.texture, hit->vec, vertical_hit);
	draw_wall_slice(cub, r, &wall);
}
