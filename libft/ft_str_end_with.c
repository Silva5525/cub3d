/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_end_with.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:22:56 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/14 10:44:12 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Checks if the string `str` ends with the string `end`.
/// @param str to check if it ends with `end`.
/// @param end to check if `str` ends with it.
/// @return true if `str` ends with `end`, false otherwise.
bool	ft_str_end_with(const char *str, const char *end)
{
	size_t	str_len;
	size_t	end_len;

	if (!str || !end)
		return (false);
	str_len = ft_strlen(str);
	end_len = ft_strlen(end);
	if (str_len < end_len)
		return (false);
	return (ft_strncmp(str + str_len - end_len, end, end_len) == 0);
}

// int	main(void)
// {
// 	char	*str = "Hello World!";
// 	char	*end = "World!";

// 	if (ft_str_end_with(str, end))
// 		puts("Ends with World!");
// 	else
// 		puts("Does not end with World!");
// 	return (EXIT_SUCCESS);
// }
