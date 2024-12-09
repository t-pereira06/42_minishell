/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:55:04 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/09 14:26:07 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	do_builtin_child(char **query)
{
	//(void)query;
	if (!(ft_strncmp(query[0], "cd", 2)))
		exec_cd_child();
	else if (!(ft_strncmp(query[0], "export", 6)))
		exec_export_child();
	else if (!(ft_strncmp(query[0], "unset", 5)))
		exec_unset_child();
	/* if (!(ft_strncmp(query[0], "echo", 4)))
		ft_echo(query);
	else if (!(ft_strncmp(query[0], "env", 3)))
		ft_env(query);
	else if (!(ft_strncmp(query[0], "pwd", 3)))
		ft_pwd();
	else if (!(ft_strncmp(query[0], "exit", 4)))
		ft_exit(); */
	return (0);
}

int exec_parent_builtins(void)
{
    ms()->query = splitter(ms()->args[0], ' ');
    if (!ms()->query)
		return (0);
    //it will also have the expander on this function
	//check_expand_quotes(ms()->args, ms);
	if (match_strings("cd", ms()->query[0]))
		exec_cd();
	else if (match_strings("export", ms()->query[0]))
		exec_export();
	else if (match_strings("unset", ms()->query[0]))
		exec_unset();
	/* else if (match_strings("export", ms()->query[0]))
		exec_export();
	else if (match_strings("exit", ms()->query[0]))
		exec_exit(); */
	return (0);
    //still underwork
}
