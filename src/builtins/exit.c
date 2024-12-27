/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:10:19 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/27 12:12:19 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	exec_exit_child(void)
{
	int	i;

	i = 0;
	if (ft_dpcount(ms()->query) > 2)
		print_many_args();
	while (ms()->query[++i])
		if (!ft_isnumeric(ms()->query[i]))
			print_non_numeric_arg(ms()->query[i]);
	if (ft_dpcount(ms()->query) == 1)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		g_exit_status = 0;
	}
	else if (ft_dpcount(ms()->query) == 2)
		convert_number_exit();
	free_child(NULL, 0);
	exit (g_exit_status);
}

void	exec_exit(void)
{
	int		count;
	int		child_status;

	count = ft_dpcount(ms()->query);
	wait(&child_status);
	if (WIFEXITED(child_status))
		g_exit_status = WEXITSTATUS(child_status);
	/* if (g_exit_status != 1 || (g_exit_status == 1 && count == 2))
	{
		free_program(1);
		exit (g_exit_status);
	} */
	free_program(1);
	exit (g_exit_status);
}
