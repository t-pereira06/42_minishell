/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:28:23 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/07 15:10:48 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Executes a single command in the minishell.
 *
 * @param ms  The `t_minishell` structure containing relevant data.
 * @param cmd The command to execute.
 */
void	exec_single_cmd(t_minishell *ms, char *cmd)
{
	char	**cmd_query;

	ms->pid[0] = fork();
	if (!ms->pid[0])
	{
		signal_default();
		//cmd_query = handle_redirects(ms, cmd);
		//redirect(ms->in_fd, ms->out_fd);
		//expand_args(cmd_query, ms);
		parse_query(ms, cmd_query);
	}
}

/**
 * Function with instructions to execute single or multiple commands
 * in the minishell.
 *
 * @param ms The `t_minishell` structure containing relevant data.
 */
void	execute(t_minishell *ms)
{
	char	*cmd;

	cmd = 0;
	if (ms->n_pipe > 0)
	{
		//exec_multi_cmd(ms);
		get_exit_status(ms);
		free_program(ms, 0);
	}
	else
	{
		cmd = add_whitespaces(ms->args[0]);
		//ms->query = remove_redirects(cmd);
		exec_single_cmd(ms, cmd);
		free(cmd);
		//check_builtins(ms, ms->query);
		ft_free_split(ms->query);
	}
	get_exit_status(ms);
	free_program(ms, 0);
}
