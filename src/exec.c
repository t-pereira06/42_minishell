/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:28:23 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/29 12:44:37 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	exec_command(t_minishell *ms, char **query)
{
	char	*command;

	if (!query[0])
		free_child(ms, query, 1);
	if (do_builtin(ms, query))
		return ;
	command = get_command(query[0], ms, 0);
	if (!command)
		no_command_err(query[0], query, ms);
	execve(command, query, ft_envcpy(ms->env));
}

void	single_cmd(t_minishell *ms, char *cmd)
{
	char	**query;

	ms->pid[0] = fork();
	if (!ms->pid[0])
	{
		signal_default();
		query = check_redir(ms, cmd, -1, -1);
		check_expand(ms, query);
		exec_command(ms, query);
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

	cmd = add_whitespaces(ms->args[0]);
	//ms->query = handle_query(ms, cmd);
	single_cmd(ms, cmd);
	free(cmd);
	//ft_free_split(ms->query);
	get_exit_status(ms);
	free_program(ms, 0);
}
