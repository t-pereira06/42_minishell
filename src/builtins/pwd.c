/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:20:56 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/30 17:15:51 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Executes the `pwd` command in a child process.
 *
 * Checks if invalid options are provided. If valid, prints the current working
 * directory. Frees resources and exits with the appropriate exit status.
 */
void	exec_pwd_child(void)
{
	char	*temp;

	temp = getcwd(0, 0);
	if (ft_dpcount(ms()->query) != 1 && ft_chrcmp(ms()->query[1][0], '-'))
	{
		printf("minishell: pwd: no options allowed\n");
		free(temp);
		g_exit_status = 2;
		free_child(NULL, 0);
		exit(g_exit_status);
	}
	printf("%s\n", temp);
	free(temp);
	g_exit_status = 0;
	free_child(NULL, 0);
	exit (g_exit_status);
}
