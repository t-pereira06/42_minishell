/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:55:04 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/02 20:34:50 by tsodre-p         ###   ########.fr       */
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
