/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:10:19 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/27 11:01:00 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	print_exit_error(void)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_putstr_fd("minishell: exit: too many arguments\n", STDOUT_FILENO);
	g_exit_status = 1;
}

void	convert_number_exit(void)
{
	int	nbr_size;

	nbr_size = 0;
	nbr_size = ft_nbrlen(ft_atoll(ms()->query[1]));
	if (ft_chrcmp(ms()->query[1][0], '+'))
		nbr_size++;
	if ((int)ft_strlen(ms()->query[1]) != nbr_size)
	{
		numeric_error(ms()->query[1]);
		g_exit_status = 2;
		free_child(NULL, 0);
		exit (g_exit_status);
	}
	g_exit_status = (ft_atoi(ms()->query[1]) % 256);
	free_child(NULL, 0);
	exit (g_exit_status);
}

void	numeric_error(char *str)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDOUT_FILENO);
}

void	exec_exit_child(void)
{
	int	i;

	i = 0;
	while (ms()->query[++i])
	{
		if (!ft_isnumeric(ms()->query[i]))
		{
			numeric_error(ms()->query[i]);
			g_exit_status = 2;
			free_child(NULL, 0);
			exit (g_exit_status);
		}
	}
	if (ft_dpcount(ms()->query) == 1)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		g_exit_status = 0;
	}
	else if (ft_dpcount(ms()->query) == 2)
		convert_number_exit();
	else
		print_exit_error();
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
	if (g_exit_status != 1 || (g_exit_status == 1 && count == 2))
	{
		free_program(1);
		exit (g_exit_status);
	}
}
