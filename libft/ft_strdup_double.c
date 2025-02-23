/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:50:07 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/23 15:50:08 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief helper function for ft_strdup_double
static void	strdup_helper(char **str, char **copy, int i)
{
	while (str[i])
	{
		copy[i] = ft_strdup(str[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return ;
		}
		i++;
	}
}

/// @brief duplicates a double pointer string array.
/// @param str double pointer string array to duplicate.
/// @return copy of the double pointer string array.
char	**ft_strdup_double(char **str)
{
	int		i;
	char	**copy;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	strdup_helper(str, copy, i);
	copy[i] = NULL;
	return (copy);
}

// int	main(void)
// {
// 	char	**str;
// 	char	**copy;
// 	int		i;

// 	str = (char **)malloc(sizeof(char *) * 3);
// 	if (!str)
// 		return (EXIT_FAILURE);
// 	str[0] = ft_strdup("Hello");
// 	str[1] = ft_strdup("World");
// 	str[2] = NULL;
// 	copy = ft_strdup_double(str);
// 	i = 0;
// 	while (copy[i])
// 	{
// 		ft_putstr_fd(copy[i], 1);
// 		ft_putchar_fd('\n', 1);
// 		free(copy[i]);
// 		i++;
// 	}
// 	free(copy);
// 	free(str[0]);
// 	free(str[1]);
// 	free(str);
// 	return (EXIT_SUCCESS);
// }
