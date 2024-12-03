/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:28:23 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/03 00:15:32 by tsodre-p         ###   ########.fr       */
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
		free_child(query, 1);
	if (do_builtin(query))
		return ;
	command = get_command(query[0], 0);
	if (!command)
		no_command_err(query[0], query);
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
	char	**query;

	if(ms()->heredoc == true)
		wait (0);
	ms()->pid[n_pid] = fork();
	if (!ms()->pid[n_pid])
	{
		signal_default();
		query = check_redir(command, -1, -1);
		manage_pipeline_io(n_pid);
		//still need to do expand
		check_expand_quotes(query);
		exec_command(query);
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
		command = add_whitespaces(ms()->args[i]);
		//check_heredoc(ms(), i);
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
	//char	**query;

	ms()->pid[0] = fork();
	if (!ms()->pid[0])
	{
		signal_default();
		ms()->query = check_redir(cmd, -1, -1);
		//still need to do expand
		check_expand_quotes(ms()->query);
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
		cmd = add_whitespaces(ms()->args[0]);
		//ms()->query = handle_query(cmd);
		single_cmd(cmd);
		exec_parent_builtins();
		free(cmd);
		//ft_free_split(ms->query);
	}
	get_exit_status();
	free_program(0);
}
