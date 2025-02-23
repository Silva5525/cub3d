/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:41:01 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/23 15:47:06 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief helper function for ft_fill
/// @param map map to test
/// @param x begin x position
/// @param y begin y position
/// @param max size of the map x & y
/// @return true if the map is enclosed by walls & false if not.
static bool	flood_l(char **map, int x, int y, t_xy *max)
{
	if (x < 0 || y < 0 || x >= max->x || y >= max->y)
		return (false);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (true);
	if (map[y][x] == ' ')
		return (false);
	map[y][x] = 'F';
	if (!flood_l(map, x + 1, y, max))
		return (false);
	if (!flood_l(map, x - 1, y, max))
		return (false);
	if (!flood_l(map, x, y + 1, max))
		return (false);
	if (!flood_l(map, x, y - 1, max))
		return (false);
	return (true);
}

/// @brief tests if the map is enclosed by walls.
/// @param map map to test
/// @param size of the map x & y
/// @param begin in the map x & y
/// @return true if the map is enclosed by walls & false if not.
bool	ft_fill(char **map, t_xy size, t_xy begin)
{
	char	**map_copy;
	int		i;
	bool	out;

	map_copy = ft_strdup_double(map);
	out = flood_l(map_copy, begin.x, begin.y, &size);
	i = 0;
	while (i < size.y)
		free(map_copy[i++]);
	free(map_copy);
	return (out);
}

/// TEST MAIN ///#######################################################
// #include <stdlib.h>
// #include <stdio.h>

// char **make_area(char **zone, t_xy size)
// {
// 	char	**new;
// 	int		i;
// 	int		j;
// 	new = malloc(sizeof(char*) * size.y);
// 	i = 0;
// 	while (i < size.y)
// 	{
// 		j = 0;
// 		new[i] = malloc(size.x + 1);
// 		while (j < size.x)
// 		{
// 			new[i][j] = zone[i][j];
// 			j++;
// 		}
// 		new[i][size.x] = '\0';
// 		i++;
// 	}
// 	return new;
// }

// int main(void)
// {
// 	int i;
// 	t_xy size = {8, 6};
// 	t_xy begin = {6, 1};
// 	char *zone[] = 
// 	{
// 		"11111111",
// 		"10001001",
// 		"10010001",
// 		"10110001",
// 		"11100001",
// 		"11111111"
// 	};
// 	char** area = make_area(zone, size);
// 	i = 0;
// 	while (i < size.y)
// 	{
// 		printf("%s\n", area[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	flood_fill(area, size, begin);
// 	i = 0;
// 	while (i < size.y)
// 	{
// 		printf("%s\n", area[i]);
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }