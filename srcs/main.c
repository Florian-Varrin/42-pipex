/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:55:10 by fvarrin           #+#    #+#             */
/*   Updated: 2022/03/27 14:33:03 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

#include <stdlib.h>
#include <sys/wait.h>

void	exit_error(char *message, int code)
{
	ft_perror(message);
	exit(code);
}

int	main(int argc, char **argv, char **envp)
{
	int			i;
	int			*pids;
	int			**pipes;
	int			number_of_child_processes;
	t_programs	*programs;

	programs = create_programs(argc, argv);
	number_of_child_processes = count_child_process(argc);
	pipes = NULL;
	pids = NULL;
	pipes = create_pipes(number_of_child_processes, pipes);
	pids = create_processes(programs, pids, pipes, envp);
	i = 0;
	close_pipes_in_main_process(pipes, number_of_child_processes);
	while ((i++) < number_of_child_processes)
		wait(NULL);
	destroy_pipes(number_of_child_processes, pipes);
	free(pids);
	return (0);
}
