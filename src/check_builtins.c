/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:55:04 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/17 15:38:28 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	do_builtin(t_minishell *ms, char **query)
{
	if (!(ft_strncmp(query[0], "echo", 4)))
	{
		ft_echo(ms, query);
		return (1);
	}
	else if (!(ft_strncmp(query[0], "env", 3)))
	{
		ft_env(ms, query);
		return (1);
	}
	else if (!(ft_strncmp(query[0], "cd", 2)))
	{
		ft_cd(ms ,query);
		return (1);
	}
	return (0);
}
