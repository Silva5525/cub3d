/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcwords.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:44:17 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/11 14:50:06 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief  Counts the number of words in a string
/// @param str the string to count the words in
/// @param delimeter to sepereate the words
/// @return the countet number of words till the null terminator
ssize_t	ft_strcwords(char *str, char delimeter)
{
	ssize_t		i;
	ssize_t		count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != delimeter && (i == 0
				|| str[i - 1] == delimeter))
			count++;
		i++;
	}
	return (count);
}
