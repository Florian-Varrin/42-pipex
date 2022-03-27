/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:25:23 by fvarrin           #+#    #+#             */
/*   Updated: 2022/03/27 16:30:37 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

t_program	*create_program(char *program_str)
{
	t_program	*program;
	char		**arguments;
	int			i;
	int			number_or_arguments;

	program = (t_program *)malloc(sizeof(t_program));
	arguments = ft_split(program_str, ' ');
	program->path = ft_strjoin("/", arguments[0]);
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

/**
 *
 * Find the program full path with the PATH env variable
 *
 * @param {t_program *} program
 *
 * @return {char *} Program path
 */
static char	*get_program_path(t_program *program)
{
	int		i;
	char	**paths;
	char	*program_path;

	i = 0;
	paths = NULL;
	while (paths == NULL)
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			paths = ft_split((environ[i] + 5), ':');
		else
			i++;
	}
	i = 0;
	while (paths[i])
	{
		program_path = ft_strjoin(paths[i], program->path);
		if (access(program_path, X_OK) == F_OK)
			break ;
		else
		{
			free(program_path);
			program_path = NULL;
		}
		i++;
	}
	return (program_path);
}

/**
 *
 * Redirect stdin and stdout to either pipe or file.
 *
 * @param {t_programs *} programs
 * @param {int **} pipes
 * @param {int} index
 */
static void	route_program_io(t_programs *programs, int **pipes, int index)
{
	int		infile_fd;
	int		outfile_fd;

	if (index == 0)
	{
		infile_fd = open_file(programs->infile, O_RDONLY);
		dup2(infile_fd, STDIN_FILENO);
		close(pipes[index][0]);
	}
	else
	{
		dup2(pipes[index][0], STDIN_FILENO);
		close(pipes[index][0]);
	}
	if (index == programs->number_of_programs - 1)
	{
		outfile_fd = open_file(programs->outfile, O_WRONLY);
		dup2(outfile_fd, STDOUT_FILENO);
		close(pipes[index + 1][1]);
	}
	else
	{
		dup2(pipes[index + 1][1], STDOUT_FILENO);
		close(pipes[index + 1][1]);
	}
}

void	execute_program(t_programs *programs, int **pipes, int index)
{
	t_program	*program;
	char		*program_path;

	route_program_io(programs, pipes, index);
	program = programs->programs[index];
	program_path = get_program_path(program);
	if (program_path == NULL)
		exit_error(ERR_EXECUTING_BIN, -4);
	if (execve(program_path, program->argv, environ) == -1)
	{
		destroy_programs(programs);
		destroy_pipes(programs->number_of_programs, pipes);
		free(program_path);
	}
}
