/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:55:04 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/02 21:29:30 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	do_builtin(char **query)
{
	if (!(ft_strncmp(query[0], "echo", 4)))
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
		ft_exit();
	return (0);
}

int exec_parent_builtins(void)
{
    ms()->query = splitter(ms()->args[0], ' ');
    if (!ms()->query)
		return ;
    //it will also have the expander on that function
	//check_expand_quotes(ms()->args, ms);
	if (check_strcmp("exit", ms()->query[0]))
		check_exit(ms, ms()->args);
	else if (check_strcmp("export", ms()->query[0]))
		check_export(ms, ms()->args);
	else if (check_strcmp("unset", ms()->query[0]))
		check_unset(ms, ms()->args);
	else if (check_strcmp("cd", ms()->query[0]))
		check_cd(ms, ms()->args);
    //still underwork
}
