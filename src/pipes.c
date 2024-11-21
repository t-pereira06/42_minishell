/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:53:28 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/11/21 00:00:36 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Closes the file descriptors associated with the pipes used in
 * piped commands.
 *
 * @param ms The t_minishell structure containing relevant data.
 */
void	close_pipes_fd(int i)
{
	while (i < ms()->n_pipe * 2)
		close(ms()->pipe_fd[i++]);
}

/**
 * Changes the standard input and output file descriptors.
 *
 * This function uses `dup2` to redirect the standard input
 * and standard output to the specified file descriptors.
 * It is commonly used to set up I/O redirection for commands
 * in a shell or pipeline.
 *
 * @param in_fd  The file descriptor to be used for standard input.
 * @param out_fd The file descriptor to be used for standard output.
 */
void	change_standard_io(int in_fd, int out_fd)
{
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
}

/**
 * Manages the input and output redirections for commands in a pipeline.
 *
 * This function configures the standard input and output file descriptors
 * for a given command in a pipeline based on its position
 * (indicated by `n_pid`).
 *
 * It ensures that the correct file descriptors are assigned for
 * piping between processes, enabling seamless data flow in a pipeline.
 *
 * @param n_pid The process ID (or index) of the current command
 * in the pipeline.
 */
void	manage_pipeline_io(int n_pid)
{
	if (!n_pid)
		change_standard_io(ms()->in_fd, ms()->pipe_fd[1]);
	else if (n_pid == ms()->n_pipe)
		change_standard_io(ms()->pipe_fd[n_pid * 2 - 2], ms()->out_fd);
	else
		change_standard_io(ms()->pipe_fd[n_pid * 2 - 2],
							ms()->pipe_fd[n_pid * 2 + 1]);
	close_pipes_fd(0);
	change_standard_io(ms()->in_fd, ms()->out_fd);
}

/**
 * Creates multiple pipes for inter-process communication.
 *
 * @param ms The minishell structure.
 */
void	do_pipex(void)
{
	int	i;

	i = 0;
	while (i < ms()->n_pipe)
	{
		if (pipe(ms()->pipe_fd + (i * 2)) < 0)
		{
			ft_putstr_fd(ERR_PIPE, STDERR_FILENO);
			free_child(NULL, 1);
		}
		i++;
	}
}
