/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:13:01 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/10 20:42:45 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

/// @brief counts the leng of s
/// @param s str to count
/// @return leng of count
size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s && s[c] != 0)
		c++;
	return (c);
}

// int array_size = sizeof(numbers) / sizeof(numbers[0]);

// #include <stdio.h>
// int	main(void)
// {
// 	char	str[] = "abcdefergg";
// 	int	out = ft_strlen(str);
// 	printf("%i", out);
// 	return (EXIT_SUCCESS);
// }
