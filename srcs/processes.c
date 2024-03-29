/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:55:46 by fvarrin           #+#    #+#             */
/*   Updated: 2022/04/23 15:09:07 by fvarrin          ###   ########.fr       */
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

int	*create_processes(t_programs *programs, int *pids, int **pipes)
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
			exit_error(MSG_FORKING_PROCESS, ERR_FORKING_PROCESS);
		if (pids[i] == 0)
		{
			close_pipes_in_child_process(pipes, number_of_child_processes, i);
			execute_program(programs, pipes, i);
		}
		i++;
	}
	return (pids);
}
