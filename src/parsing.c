/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:55:45 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/07 15:06:01 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
/**
 * Parses and executes the command query.
 *
 * @param ms         Pointer to the minishell structure.
 * @param cmd_query  The command query as an array of strings.
 */
void	parse_query(t_minishell *ms, char **cmd_query)
{
	char	*command;

	/* if (!cmd_query[0])
		free_child(ms, cmd_query, 1);
	if (check_if_builtin(ms, cmd_query))
		return ;
	if (!check_files(cmd_query, ms))
		file_error(cmd_query, ms);
	command = get_command(cmd_query[0], ms, 0);
	if (!command)
		cmd_err(cmd_query[0], cmd_query, ms);
	else if (check_strcmp("NO_PATH_AVAILABLE", command))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_query[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free_child(ms, cmd_query, 0);
		g_exit = 127;
		exit (g_exit);
	} */
	execve(command, cmd_query, ft_envcpy(ms->env));
}
