/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:55:04 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/11/05 12:12:26 by tsodre-p         ###   ########.fr       */
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
	return (0);
}
