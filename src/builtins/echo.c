/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:04:51 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/30 17:12:51 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Validates the `echo` command options and updates the `echo_option` flag.
 *
 * @return
 *   - 0 if no arguments or only `-n` is specified,
 *   - 1 if `-n` is valid with additional arguments or otherwise.
 */
int	check_echo_option(void)
{
	if (!ms()->query[1])
		return (ft_putstr_fd("\n", ms()->out_fd), 0);
	else if (match_strings(ms()->query[1], "-n") && !ms()->query[2])
		return (0);
	else if (match_strings(ms()->query[1], "-n"))
		return (ms()->echo_option = true, 1);
	return (1);
}

/**
 * Prints the arguments of the `echo` command starting from a given position.
 *
 * @param start_pos The index of the first argument to print.
 * If the `-n` option is not set, appends a newline at the end.
 */
void	print_echo(int start_pos)
{
	int	i;

	i = start_pos;
	while (ms()->query[i])
	{
		ft_putstr_fd(ms()->query[i], ms()->out_fd);
		if (ms()->query[i + 1])
			ft_putchar_fd(' ', ms()->out_fd);
		i++;
	}
	if (!ms()->echo_option)
		ft_putstr_fd("\n", ms()->out_fd);
}

/**
 * Executes the `echo` command in a child process.
 *
 * Depending on the presence of the `-n` option, it prints arguments
 * starting from the appropriate position. Sets the exit status to 0,
 * frees child resources, and exits the process.
 */
void	exec_echo_child(void)
{
	if (check_echo_option())
	{
		if (!ms()->echo_option)
			print_echo(1);
		else
			print_echo(2);
	}
	g_exit_status = 0;
	free_child(NULL, 0);
	exit (0);
}
