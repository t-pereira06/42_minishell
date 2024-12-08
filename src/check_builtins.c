/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:55:04 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/08 17:20:33 by tsodre-p         ###   ########.fr       */
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
	/* if (!(ft_strncmp(query[0], "echo", 4)))
		ft_echo(query);
	else if (!(ft_strncmp(query[0], "env", 3)))
		ft_env(query);
	else if (!(ft_strncmp(query[0], "cd", 2)))
		ft_cd(query);
	else if (!(ft_strncmp(query[0], "export", 6)))
		ft_export(query);
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
	if (check_strcmp("cd", ms()->query[0]))
		exec_cd();
	if (check_strcmp("export", ms()->query[0]))
		exec_export();
	/* else if (check_strcmp("export", ms()->query[0]))
		exec_export();
	else if (check_strcmp("unset", ms()->query[0]))
		exec_unset();
	else if (check_strcmp("exit", ms()->query[0]))
		exec_exit(); */
	return (0);
    //still underwork
}
