/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:21:50 by fvarrin           #+#    #+#             */
/*   Updated: 2022/04/23 14:07:52 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <fcntl.h>

int	open_file(char *path, int flags)
{
	int		fd;

	fd = open(path, flags);
	if (fd < 0)
		exit_error(path, ERR_OPENING_FILE);
	return (fd);
}
