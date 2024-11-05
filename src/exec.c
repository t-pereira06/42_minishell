/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:28:23 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/11/05 12:20:52 by tsodre-p         ###   ########.fr       */
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

	cmd = add_whitespaces(ms()->args[0]);
	//ms()->query = handle_query(cmd);
	single_cmd(cmd);
	free(cmd);
	//ft_free_split(ms->query);
	get_exit_status();
	free_program(0);
}
