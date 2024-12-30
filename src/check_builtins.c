/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:55:04 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 17:17:24 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Executes the appropriate built-in command in a child process.
 *
 * Identifies the built-in command from the `ms()->query[0]` and calls the
 * corresponding function for `cd`, `export`, `unset`, `pwd`, `env`, `echo`
 * or `exit`.
 *
 * @return Always returns 0.
 */
int	do_builtin_child(void)
{
	if (match_strings("cd", ms()->query[0]))
		exec_cd_child();
	else if (match_strings("export", ms()->query[0]))
		exec_export_child();
	else if (match_strings("unset", ms()->query[0]))
		exec_unset_child();
	else if (match_strings("pwd", ms()->query[0]))
		exec_pwd_child();
	else if (match_strings("env", ms()->query[0]))
		exec_env_child();
	if (match_strings("echo", ms()->query[0]))
		exec_echo_child();
	else if (match_strings("exit", ms()->query[0]))
		exec_exit_child();
	return (0);
}

/**
 * Executes the appropriate built-in command in the parent process.
 *
 * Splits the input arguments, expands any quotes, and identifies the built-in
 * command to call (`cd`, `export`, `unset`, or `exit`).
 *
 * @return Always returns 0.
 */
int	exec_parent_builtins(void)
{
	ms()->query = splitter(ms()->args[0], ' ');
	if (!ms()->query)
		return (0);
	check_expand_quotes(ms()->query);
	if (match_strings("cd", ms()->query[0]))
		exec_cd();
	else if (match_strings("export", ms()->query[0]))
		exec_export();
	else if (match_strings("unset", ms()->query[0]))
		exec_unset();
	else if (match_strings("exit", ms()->query[0]))
		exec_exit();
	return (0);
}
