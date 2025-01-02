/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:28:23 by tsodre-p          #+#    #+#             */
/*   Updated: 2025/01/02 20:31:47 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Executes a command by handling builtins and invoking the external command.
 *
 * This function first checks if the command is a builtin and executes it if so.
 * If not, it attempts to locate the command and execute it using `execve`.
 * If the command cannot be found, an error is raised.
 *
 * @param query The parsed command arguments, where `query[0]` is the
 * command to execute.
 */
void	exec_command(char **query)
{
	char	*command;

	if (!query[0])
	{
		free_child(NULL, 0);
		exit (0);
	}
	if (do_builtin_child())
		return ;
	if (check_if_dir_file(query[0]))
		return ;
	command = find_executable_path(query[0], 0);
	if (!command)
		no_cmd_err(query[0]);
	execve(command, query, ft_envcpy(ms()->env));
}

/**
 * Executes a command in a pipeline after handling redirections and I/O.
 *
 * This function forks a process to execute a command in the pipeline.
 * It handles redirections, manages input/output redirections for the
 * pipeline, and expands variables/quotes before executing the command.
 *
 * @param command The command to be executed in the pipeline.
 * @param n_pid The index of the current process in the pipeline,
 * used to manage I/O.
 */
void	exec_command_pipe(char *command, int n_pid)
{
	if (ms()->heredoc == true)
		wait (0);
	ms()->pid[n_pid] = fork();
	if (!ms()->pid[n_pid])
	{
		signal_default();
		ms()->query = check_redir(command, -1, -1);
		manage_pipeline_io(n_pid);
		exec_command(ms()->query);
	}
}

/**
 * Executes commands in a pipeline.
 *
 * This function iterates over each command in the pipeline,
 * adds necessary whitespace, executes the command using `exec_command_pipe`,
 * and frees allocated memory.
 * It also ensures that the pipe file descriptors are closed after execution.
 *
 */
void	exec_pipes(void)
{
	char	*command;
	int		i;

	i = -1;
	while (ms()->args[++i])
	{
		command = format_input(ms()->args[i], 0, 0);
		exec_command_pipe(command, i);
		free(command);
	}
	close_pipes_fd(0);
}

/**
 * Executes a single command by forking a new process.
 *
 * This function forks the current process and, in the child process,
 * processes the command by checking for redirections, expanding variables
 * and executing the command.
 *
 * @param cmd The command string to be executed.
 */
void	single_cmd(char *cmd)
{
	ms()->pid[0] = fork();
	if (!ms()->pid[0])
	{
		signal_default();
		ms()->query = check_redir(cmd, -1, -1);
		exec_command(ms()->query);
	}
}

/**
 * Function with instructions to execute single or multiple commands
 * in the minishell.
 *
 * @param ms The `t_minishell` structure containing relevant data.
 */
void	execute(void)
{
	char	*cmd;

	if (ms()->n_pipe != 0)
	{
		ms()->pipe_fd = ft_calloc(ms()->n_pipe * 2, sizeof(int));
		if (!ms()->pipe_fd)
		{
			ft_putstr_fd(ERR_PIPE, STDERR_FILENO);
			free_child(NULL, 1);
		}
		do_pipex();
		exec_pipes();
	}
	else
	{
		cmd = format_input(ms()->args[0], 0, 0);
		single_cmd(cmd);
		free(cmd);
		exec_parent_builtins();
	}
	get_exit_status();
	free_program(0);
}
