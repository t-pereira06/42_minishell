/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:23:19 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/07 12:30:52 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Updates the current state of quotation marks in a string.
 *
 * @param c The current character being evaluated.
 * @param quote The current state of quotation marks.
 *
 * @return Returns the updated state of quotation marks based on the
 * character evaluation.
 */
char	get_quote(char c, char quote)
{
	if (ft_strrchr("\"\'", c) && !quote)
		return (c);
	else if (ft_strrchr("\"\'", c) && quote == c)
		return (0);
	return (quote);
}

/**
 * Prints an error message indicating an invalid operator.
 *
 * @param error The error message to be displayed.
 * @param operator The invalid operator causing the error.
 * @return Returns 1.
 */
int	error_operator(char *error, char *operator)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(operator, STDERR_FILENO);
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
int	error_token(char *error, char metachar, int dup)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putchar_fd(metachar, STDERR_FILENO);
	if (dup == 1)
		ft_putchar_fd(metachar, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (1);
}

/**
 * Checks for unexpected tokens and redirects in the input string.
 *
 * @param input The input string to check.
 * @return 0 if no unexpected tokens or redirects are found, 1 otherwise.
 */
int	unexpected_tokens(char *input)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (input[++i])
	{
		quote = get_quote(input[i], quote);
		if (input[i] == '|' && input[i + 1] == ' ' && !quote)
		{
			i++;
			while (input[i] && input[i] == ' ')
				i++;
			if (input[i] && input[i] == ' ')
				return (error_token(UNTOKEN, '|', 0));
		}
		else if (ft_strrchr(REDIRECT, input[i]) && !quote)
			if (unexpected_redirect(input, &i))
				return (1);
	}
	return (0);
}

/**
 * Checks for unexpected redirect tokens and raises corresponding errors.
 *
 * @param input The input string.
 * @param i Pointer to the current position in the input string.
 * @return Returns 1 if an error occurs, 0 otherwise.
 */
int	unexpected_redirect(char *input, int *i)
{
	if (input[*i] == input[*i + 1])
		(*i)++;
	(*i)++;
	if (input[*i] == ' ')
		while (input[*i] && input[*i] == ' ')
			(*i)++;
	if (input[*i] == '|')
		return (error_token(UNTOKEN, '|', 0));
	else if (input[*i - 1] == '>' && input[*i] == '|')
		return (error_operator(NOSUPPORT, ">|"));
	else if (ft_strrchr(REDIRECT, input[*i]) && !input[*i])
		return (error_operator(UNTOKEN, "newline"));
	else if (ft_strrchr(REDIRECT, input[*i]) && input[*i] != input[*i + 1])
		return (error_token(UNTOKEN, input[*i], 0));
	else if (ft_strrchr(REDIRECT, input[*i]) && input[*i] == input[*i + 1])
		return (error_token(UNTOKEN, input[*i + 1], 1));
	return (0);
}
