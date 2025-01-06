/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:13:17 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/06 19:25:23 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief checks if the map is surrounded by walls
/// @param map_width 
/// @param map_height 
/// @param map to check
/// @return true if the map is surrounded by walls, false otherwise
bool	ft_check_wall(size_t map_width, size_t map_height, char **map)
{
	size_t	i;

	i = 0;
	while (i < map_width)
	{
		if (map[0][i] != '1' || map[map_height - 1][i] != '1')
			return (false);
		i++;
	}
	while (i < map_height)
	{
		if (map[i][0] != '1' || map[i][map_width - 1] != '1')
			return (false);
		i++;
	}
	return (true);
}

// int	main(void)
// {
// 	char	**map;
// 	size_t	map_width;
// 	size_t	map_height;

// 	map = ft_split("111\n101\n111", '\n');
// 	map_width = 3;
// 	map_height = 3;
// 	if (ft_check_wall(map_width, map_height, map))
// 		puts("Wall is closed");
// 	else
// 		puts("Wall is not closed");
// 	return (0);
// }
