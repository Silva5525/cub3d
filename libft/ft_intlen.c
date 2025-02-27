/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:06:16 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/14 10:23:00 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief counts the number of digits in an integer (+ the - sign)
/// @param n the integer to count
/// @return the length of the integer
int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (EXIT_FAILURE);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

// int	main(void)
// {
// 	int	n;

// 	n = 123456789;
// 	printf("The number of digits in %d is %d\n", n, ft_intlen(n));
// 	n = -123456789;
// 	printf("The number of digits in %d is %d\n", n, ft_intlen(n));
// 	n = 0;
// 	printf("The number of digits in %d is %d\n", n, ft_intlen(n));
// 	return (EXIT_SUCCESS);
// }
