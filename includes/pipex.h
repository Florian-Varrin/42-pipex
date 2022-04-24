/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:06:10 by fvarrin           #+#    #+#             */
/*   Updated: 2022/04/23 15:10:03 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define MSG_INVALID_NUMBER_ARGUMENT "Invalid number of arguments\n"
# define MSG_CREATING_PIPE "Error while creating pipes\n"
# define MSG_FORKING_PROCESS "Error while forking process\n"
# define MSG_EXECUTING_BIN "command not found: %s\n"

# define FILE_PERMISSION_IF_CREATED 0664

extern char	**environ;

typedef struct s_program {
	char	*path;
	char	*name;
	char	**argv;
	int		return_value;
}	t_program;

typedef struct s_programs {
	char		*infile;
	char		*outfile;
	t_program	**programs;
	int			number_of_programs;
}	t_programs;

/**
 * Error codes :
 * 1: Invalid number of arguments
 * 2: Error while opening file
 * 3: Error forking process
 * 4: Command not found
 *
 */
typedef enum e_error_codes {
	ERR_INVALID_NUMBER_ARGUMENTS = 1,
	ERR_OPENING_FILE = 2,
	ERR_FORKING_PROCESS = 3,
	ERR_COMMAND_NOT_FOUND = 4
}	t_error_codes;

/**
 *
 * Print message whit perror and exit with code
 *
 * @param {char *} message
 * @param {int} code
 */
void		exit_error(char *message, int code);

/**
 *
 * Open a file and return it's file descriptor. If there is an error, print
 * a message and exit program
 *
 * @param {char *} path
 * @param {int} flags
 *
 * @return {int} File descriptor
 */
int			open_file(char *path, int flags);

/**
 *
 * Free memory of the program struct
 *
 * @param {t_program *} program
 */
void		destroy_program(t_program *program);

/**
 *
 * Route the pipes to stdin / stdout and execute the program
 *
 * @param {t_programs *} programs
 * @param {int **} pipes
 * @param {int} index
 */
void		execute_program(t_programs *programs, int **pipes, int index);

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
 *
 * @return {int *} pointer on allocated pids
 */
int			*create_processes(t_programs *programs, int *pids, int **pipe);
#endif
