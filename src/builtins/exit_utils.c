/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:57:30 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 17:14:13 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Prints an error message for invalid `exit` usage.
 *
 * Displays a message indicating too many arguments and sets the exit
 * status to 1.
 */
void	print_exit_error(void)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	g_exit_status = 1;
}

/**
 * Converts and validates the numeric argument for the `exit` command.
 *
 * Ensures the argument is a valid number. If invalid, triggers a numeric
 * error, sets the exit status to 2, and exits. For valid numbers, computes
 * the exit status modulo 256, frees resources, and exits.
 */
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

/**
 * Prints an error message for an invalid numeric argument in the
 * `exit` command.
 *
 * @param str The invalid numeric argument to include in the error message.
 */
void	numeric_error(char *str)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

/**
 * Handles the error for too many arguments in the `exit` command.
 *
 * Prints an error message, sets the exit status to 1, frees resources,
 * and exits the process.
 */
void	print_many_args(void)
{
	print_exit_error();
	g_exit_status = 1;
	free_child(NULL, 0);
	exit (g_exit_status);
}

/**
 * Handles the error for a non-numeric argument in the `exit` command.
 *
 * @param str The invalid argument to include in the error message.
 * Prints an error, sets the exit status to 2, frees resources, and exits.
 */
void	print_non_numeric_arg(char *str)
{
	numeric_error(str);
	g_exit_status = 2;
	free_child(NULL, 0);
	exit (g_exit_status);
}
