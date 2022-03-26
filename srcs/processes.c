/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:55:46 by fvarrin           #+#    #+#             */
/*   Updated: 2022/03/26 16:07:21 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int	count_child_process(int argc)
{
	return (argc - 3);
}

int	count_total_process(int number_of_child_processes)
{
	return (number_of_child_processes + 1);
}

int	*create_processes(t_programs *programs, int *pids, int **pipes, char **envp)
{
	int		i;
	int		number_of_child_processes;

	number_of_child_processes = programs->number_of_programs;
	pids = malloc(sizeof(int) * number_of_child_processes);
	i = 0;
	while (i < number_of_child_processes)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			exit_error(ERR_FORKING_PROCESS, -3);
		if (pids[i] == 0)
		{
			close_pipes_in_child_process(pipes, number_of_child_processes, i);
			execute_program(programs->programs[i], pipes, i, envp);
		}
		i++;
	}
	return (pids);
}

void	handle_main_process(t_programs *programs, int **pipes)
{
	char	*str;
	int		infile_fd;
	int		outfile_fd;
	int		index_of_last_pipe;

	str = NULL;
	infile_fd = open(programs->infile, O_RDONLY);
	if (infile_fd < 0)
		exit_error(ERR_OPENING_FILE, -2);
	str = ft_get_next_line(infile_fd);
	if (write(pipes[0][1], str, ft_strlen(str)) == -1)
		exit_error(ERR_WRITING_PIPE, -4);
	while (str)
	{
		str = ft_get_next_line(infile_fd);
		if (str == NULL)
			break ;
		if (write(pipes[0][1], str, ft_strlen(str)) == -1)
			exit_error(ERR_WRITING_PIPE, -4);
	}
	close(infile_fd);
	close(pipes[0][1]);
	outfile_fd = open(programs->outfile, O_WRONLY);
	if (outfile_fd < 0)
		exit_error(ERR_OPENING_FILE, -2);
	index_of_last_pipe = count_total_process(programs->number_of_programs) - 1;
	str = ft_get_next_line(pipes[index_of_last_pipe][0]);
	if (write(outfile_fd, str, ft_strlen(str)) == -1)
		exit_error(ERR_WRITING_FILE, -5);
	while (str)
	{
		str = ft_get_next_line(pipes[index_of_last_pipe][0]);
		if (str == NULL)
			break ;
		if (write(outfile_fd, str, ft_strlen(str)) == -1)
			exit_error(ERR_WRITING_FILE, -5);
	}
	close(pipes[index_of_last_pipe][0]);
	close(outfile_fd);
}