/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:10:19 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/30 17:15:08 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Executes the `exit` command in a child process.
 *
 * Handles cases with too many arguments, non-numeric arguments, or a
 * single numeric argument. Validates input, sets the appropriate exit
 * status, frees resources, and terminates the process.
 */
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

/**
 * Executes the `exit` command in the parent process.
 *
 * Waits for the child process to terminate, retrieves its exit status,
 * frees resources, and exits the program with the appropriate exit status.
 */
void	exec_exit(void)
{
	int		child_status;

	wait(&child_status);
	if (WIFEXITED(child_status))
		g_exit_status = WEXITSTATUS(child_status);
	free_program(1);
	exit (g_exit_status);
}
