/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:17:28 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/14 10:43:43 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	count;

	if (!s || !accept)
		return (0);
	count = 0;
	while (*s && ft_strchr(accept, *s++))
		count++;
	return (count);
}

// int	main(void)
// {
// 	const char *s = "abc123";
// 	const char *accept = "abc";

// 	size_t len = ft_strspn(s, accept);
// 	printf("Length of initial segment: %zu\n", len);

// 	return (0);
// }
