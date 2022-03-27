/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:06:10 by fvarrin           #+#    #+#             */
/*   Updated: 2022/03/27 14:54:20 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define ERR_INVALID_NUMBER_ARGUMENT "Invalid number of arguments\n"
# define ERR_CREATING_PIPE "Error while creating pipes\n"
# define ERR_WRITING_PIPE "Error while writing to pipe\n"
# define ERR_FORKING_PROCESS "Error while forking process\n"
# define ERR_OPENING_FILE "Error while opening file\n"
# define ERR_WRITING_FILE "Error while writing to file\n"

typedef struct s_program {
	char	*path;
	char	**argv;
}	t_program;

typedef struct s_programs {
	char		*infile;
	char		*outfile;
	t_program	**programs;
	int			number_of_programs;
}	t_programs;

/**
 *
 * Print message and exit with code
 *
 * @param {char *} message
 * @param {int} code
 */
void		exit_error(char *message, int code);

/**
 *
 * Allocate memory and fulfil the programs struct and the program list inside it
 *
 * @param {int} argc
 * @param {char **} argv
 *
 * @return {t_programs *} Pointer to the programs struct
 */
t_programs	*create_programs(int argc, char **argv);

/**
 *
 * Route the pipes to stdin / stdout and execute the program
 *
 * @param {t_programs *} programs
 * @param {int **} pipes
 * @param {int} index
 * @param {char **} envp
 */
void		execute_program(t_programs *programs, int **pipes, int index, char **envp);

/**
 *
 * Free the memory of the programs struct and the different progams in the
 * in programs list
 *
 * @param {t_programs *} programs
 */
void		destroy_programs(t_programs *programs);

/**
 *
 * Allocate and create the pipes
 *
 * @param {int} number_of_child_processes
 * @param {int **} pipes
 *
 * @return {int **} pointer on created pipes array
 */
int			**create_pipes(int number_of_child_processes, int **pipes);

/**
 *
 * Close all unnecessary pipes for current child process
 *
 * @param {int **} pipes
 * @param {int} number_of_child_processes
 * @param {int} index
 */
void		close_pipes_in_child_process(
				int **pipes,
				int number_of_child_processes,
				int index
				);

/**
 *
 * Close all pipes for main process
 *
 * @param {int **} pipes
 * @param {int} number_of_child_processes
 */
void		close_pipes_in_main_process(
				int **pipes,
				int number_of_child_processes
				);

/**
 *
 * Free memory for the pipes
 *
 * @param {int} number_of_child_processes
 * @param {int **} pipes
 */
void		destroy_pipes(int number_of_child_processes, int **pipes);

/**
 *
 * Remove 3 to argc because first one is binary, second one is infile et last
 * one is outfile
 *
 * @param {int} argc
 *
 * @return {int} Number of child processes
 */
int			count_child_process(int argc);

/**
 *
 * Add 1 to the number of child processes for the main process
 *
 * @param {int} number_of_child_processes
 *
 * @return {int} Total number of processes
 */
int			count_total_process(int number_of_child_processes);

/**
 *
 * Fork to the right number of processes and execute the programs
 *
 * @param {t_programs *} programs
 * @param {int *} pids
 * @param {int **} pipes
 * @param {char **} envp
 *
 * @return {int *} pointer on allocated pids
 */
int			*create_processes(t_programs *programs, int *pids, int **pipes, char **envp);
#endif
