/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:57:30 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/27 12:06:35 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	print_exit_error(void)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
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
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

void	print_many_args(void)
{
	print_exit_error();
	g_exit_status = 1;
	free_child(NULL, 0);
	exit (g_exit_status);
}

void	print_non_numeric_arg(char *str)
{
	numeric_error(str);
	g_exit_status = 2;
	free_child(NULL, 0);
	exit (g_exit_status);
}