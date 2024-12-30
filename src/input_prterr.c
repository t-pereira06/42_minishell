/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_prterr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:52:03 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/22 10:21:42 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Prints a syntax error message for an invalid character.
 *
 * This function outputs an error message indicating a syntax issue with
 * a specific character in the command string.
 *
 * @param error The error message prefix.
 * @param str The string containing the invalid character.
 * @return 1, indicating an error has occurred.
 */
int	print_syntax_err(char *error, char *str)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putchar_fd(str[0], STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (1);
}

/**
 * Prints an error message indicating an invalid operator.
 *
 * @param error The error message to be displayed.
 * @param str The invalid operator causing the error.
 * @return Returns 1.
 */
int	print_op_err(char *error, char *str)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (1);
}

/**
 * Prints an error message indicating an unexpected token.
 *
 * @param error The error message to be displayed.
 * @param metachar The unexpected token causing the error.
 * @param dup Flag indicating whether the token should be duplicated in the
 * error message.
 * @return Returns 1.
 */
int	print_token_err(char *error, char metachar, int dup)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putchar_fd(metachar, STDERR_FILENO);
	if (dup == 1)
		ft_putchar_fd(metachar, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (1);
}
