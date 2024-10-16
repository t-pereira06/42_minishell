/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:06:10 by davioliv          #+#    #+#             */
/*   Updated: 2024/10/16 13:38:55 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_minishell *ms, char **query)
{
	int	i;

	i = 0;
	while (query[i])
		i++;
	if (i == 1)
	{
		free_child(ms, query, 0);
		g_exit = 0;
		exit (g_exit);
	}
	if (i > 2)
	{
		ft_putstr_fd("minishell: too many arguments\n", STDERR_FILENO);
		free_child(ms, query, 0);
		g_exit = 1;
		exit (g_exit);
	}
	chdir(query[1]);
}
