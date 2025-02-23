/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:41:01 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/23 16:05:22 by wdegraf          ###   ########.fr       */
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

// // TEST MAIN ///#######################################################

// int main(void)
// {
// 	t_xy size = {8, 6};      // Map Größe (Breite x Höhe)
// 	t_xy begin = {1, 1};     // Startposition (x, y)

// 	// Testmap: 1 = Wand, 0 = freier Bereich
// 	char **zone = {
// 		"11111111",
// 		"10N00001",
// 		"10110001",
// 		"10010001",
// 		"11100001",
// 		"11111111"
// 	};
// 	char **area = ft_strdup_double(zone);
// 	if (!area)
// 		return (printf("Error: Map allocation failed\n"), EXIT_FAILURE);
// 	printf("Map vor ft_fill:\n");
// 	for (int i = 0; i < size.y; i++)
// 		printf("%s\n", area[i]);
// 	if (ft_fill(area, size, begin))
// 		printf("\nDie Map ist geschlossen.\n");
// 	else
// 		printf("\nDie Map ist nicht geschlossen!\n");
// 	printf("\nMap nach ft_fill:\n");
// 	for (int i = 0; i < size.y; i++)
// 		printf("%s\n", area[i]);
// 	for (int i = 0; i < size.y; i++)
// 		free(area[i]);
// 	free(area);
// 	return (EXIT_SUCCESS);
// }
