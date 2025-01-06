/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:00:19 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/10 20:42:45 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief compares the two strings s1 and s2 until the first differing
/// character is found, or until n characters have been compared.
/// @param s1 searched string
/// @param s2 to compare string
/// @return 0 if equal || -1 if s1 < s2 || 1 if s1 > s2
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

// int main(void)
// {
// 	char *s1 = "Hello";
// 	char *s2 = "Helo";
// 	printf("Result: %d\n", ft_strcmp(s1, s2));
// 	return (EXIT_SUCCESS);
// }