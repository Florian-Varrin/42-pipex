/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:21:50 by fvarrin           #+#    #+#             */
/*   Updated: 2022/04/24 11:42:53 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <fcntl.h>

int	open_file(char *path, int flags)
{
	int		fd;

	fd = open(path, flags, FILE_PERMISSION_IF_CREATED);
	if (fd < 0)
		exit_error(path, ERR_OPENING_FILE);
	return (fd);
}
