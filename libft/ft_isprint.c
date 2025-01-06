/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:40:04 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/10 20:43:17 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief checks if a is an printable character.
/// @param a char representet as an int
/// @return 1 if true 0 if not true
int	ft_isprint(int a)
{
	if (a >= 32 && a <= 126)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

// #include <stdio.h>
// int	main (void)
// {
// 	char	a = 31;
// 	int	out = ft_isprint(a);
// 	printf("%i", out);
// 	return (EXIT_SUCCESS);
// }
