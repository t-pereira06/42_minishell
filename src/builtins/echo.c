/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:04:51 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/27 13:46:54 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
