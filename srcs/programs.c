/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:05:23 by fvarrin           #+#    #+#             */
/*   Updated: 2022/04/23 15:09:07 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/**
 * Allocate the memory and fulfil a program
 *
 * @param {char *} program_str - a string for the program. For instance "ls -l"
 * @return
 */
static t_program	*create_program(char *program_str)
{
	t_program	*program;
	char		**arguments;
	int			i;
	int			number_or_arguments;

	program = (t_program *)malloc(sizeof(t_program));
	arguments = ft_split(program_str, ' ');
	program->path = ft_strjoin("/", arguments[0]);
	program->name = ft_strdup(arguments[0]);
	program->return_value = 0;
	i = 0;
	number_or_arguments = 0;
	while (arguments[i++])
		number_or_arguments++;
	program->argv = (char **)malloc(sizeof(char *) * (number_or_arguments + 1));
	i = 0;
	while (i < number_or_arguments)
	{
		program->argv[i] = ft_strdup(arguments[i]);
		free(arguments[i]);
		i++;
	}
	program->argv[i] = NULL;
	free(arguments);
	return (program);
}

void	destroy_program(t_program *program)
{
	int		i;

	free(program->path);
	i = 0;
	while (program->argv[i])
		free(program->argv[i++]);
	free(program->argv);
	free(program);
}

t_programs	*create_programs(int argc, char **argv)
{
	int			i;
	t_programs	*program_list;

	if (argc < 5)
		exit_error(MSG_INVALID_NUMBER_ARGUMENT, ERR_INVALID_NUMBER_ARGUMENTS);
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
