/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:46:50 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/08 17:53:54 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_access_read_write(const char *path, int mode)
{
	int	fd;

	if (mode == O_RDONLY)
		fd = open(path, O_RDONLY);
	else if (mode == O_WRONLY)
		fd = open(path, O_WRONLY);
	else
		return (false);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}