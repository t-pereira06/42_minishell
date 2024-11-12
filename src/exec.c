/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:28:23 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/11/12 21:10:41 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

void	exec_command_pipe(char **command, int n_pid)
{
	char	**query;

	if(ms()->heredoc == true)
		wait (0);
	ms()->pid[n_pid] = fork();
	if (!ms()->pid[n_pid])
	{
		signal_default();
		query = check_redir(command, -1, -1);
		check_expand(query);
		exec_command(query);
		//stopped here, keep going
	}
}

void	exec_pipes(void)
{
	char	*command;
	int		i;

	i = -1;
	do_pipex();
	while (ms()->args[++i])
	{
		command = add_whitespaces(ms()->args[i]);
		//ms()->query = 0;
		check_heredoc(ms(), i);
		exec_command_pipe(command, i);
		free(command);
	}
	close_pipex(ms());
}

void	single_cmd(char *cmd)
{
	char	**query;

	ms()->pid[0] = fork();
	if (!ms()->pid[0])
	{
		signal_default();
		query = check_redir(cmd, -1, -1);
		check_expand(query);
		exec_command(query);
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
		exec_pipes();
	}
	cmd = add_whitespaces(ms()->args[0]);
	//ms()->query = handle_query(cmd);
	single_cmd(cmd);
	free(cmd);
	//ft_free_split(ms->query);
	get_exit_status();
	free_program(0);
}
