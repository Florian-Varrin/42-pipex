/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:05:23 by fvarrin           #+#    #+#             */
/*   Updated: 2022/03/27 16:29:28 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

t_programs	*create_programs(int argc, char **argv)
{
	int			i;
	t_programs	*program_list;

	if (argc < 5)
		exit_error(ERR_INVALID_NUMBER_ARGUMENT, -1);
	program_list = (t_programs *)malloc(sizeof(t_programs));
	program_list->outfile = ft_strdup(argv[argc - 1]);
	program_list->infile = ft_strdup(argv[1]);
	program_list->number_of_programs = argc - 3;
	program_list->programs = (t_program **)malloc(
			sizeof(t_program *) * program_list->number_of_programs);
	i = 0;
	while (i < argc - 3)
	{
		program_list->programs[i] = create_program(argv[i + 2]);
		i++;
	}
	return (program_list);
}

void	destroy_programs(t_programs *programs)
{
	int		i;

	free(programs->infile);
	free(programs->outfile);
	i = 0;
	while (i < programs->number_of_programs)
		destroy_program(programs->programs[i++]);
	free(programs->programs);
	free(programs);
}

