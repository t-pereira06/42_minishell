/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:23:19 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 18:51:14 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Checks the validity of an operator in the minishell structure.
 *
 * @param operator A string representing the operator to validate.
 *
 * @return Returns 0 if the operator is valid and supported.
 *         If the operator is recognized but unsupported, it returns the result
 *         of `print_op_err`, indicating an unsupported operator error.
 *         For unrecognized operators, it returns the result of
 *         `print_syntax_err`, indicating a syntax error with the
 *         provided operator.
 */
int	check_op(char *operator, char *input, int a)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (operator[++i])
		if (ft_strchr("&;(){}\\", operator[i]) || verify_asterisc(a))
			return (print_op_err(ERR_OP, operator));
	if (match_strings(operator, "<") || match_strings(operator, ">")
		|| match_strings(operator, "<<") || match_strings(operator, ">>")
		|| match_strings(operator, "|"))
	{
		while (input[j] == ' ')
			j++;
		if ((input[j] == '<' || input[j] == '>') && a == 0)
			return (print_op_err(ERR_TOKEN, "newline"));
		else
			return (0);
	}
	else if (match_strings(operator, "||") || match_strings(operator, "<>")
		|| match_strings(operator, "<<<") || match_strings(operator, ">|")
		|| match_strings(operator, ">>>"))
		return (print_op_err(ERR_OP, operator));
	return (0);
}

/**
 * Validates and resets the operator in the minishell structure.
 *
 * @param ms Pointer to the minishell structure containing the current operator.
 *
 * @return Returns 1 if the operator requires further handling (as indicated
 * by `check_op`), or 0 if no further handling is required. In all cases,
 * the function frees `ms->operator` and resets it to an empty string if
 * not needed.
 */
int	helper_operator(char *input, int a)
{
	int	return_val;

	return_val = check_op(ms()->operator, input, a);
	free(ms()->operator);
	if (return_val == 1)
		return (1);
	else
	{
		ms()->operator = "\0";
		return (0);
	}
}

/**
 * Checks for unmatched quotes in the query string.
 *
 * This function scans through the query string and verifies whether
 * there are any unmatched quotes (single or double quotes) present.
 *
 * @param query The query string to be checked.
 * @return 1 if an unmatched quote is found; otherwise, 0.
 */
int	search_quote(char *query)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (query[++i])
	{
		quote = get_quote(query[i], quote);
		if (quote == query[i])
			return (1);
	}
	return (0);
}

/**
 * Validates pipe syntax and checks for errors in the query string.
 *
 * This function checks if there are any improper usages of the pipe(`|`) symbol,
 * such as:
 *
 * - Pipe at the start or end of the string.
 *
 * - Missing arguments after a pipe.
 *
 * - Pipe being placed directly after a redirection operator.
 *
 * @param string The string to be checked for pipe syntax.
 * @param query The array of query arguments.
 * @param a The current index in the query array.
 * @param quote A variable tracking the current quote state.
 * @return 1 if an error is found; otherwise, 0.
 */
int	check_pipe(char *string, char**query, int a, int quote)
{
	int	i;

	i = -1;
	if (helper_check_pipe(query, a))
		return (1);
	else if (ft_strchr(string, '|') && ft_strlen(string) > 1 && !query[a + 1])
	{
		while (string[++i])
		{
			quote = get_quote(string[i], quote);
			if (string[i] == '|' && !quote)
			{
				if (a == 0)
				{
					if ((i == 0 || !string[i - 1])
						|| (i + 1 >= (int)ft_strlen(string) || !string[i + 1]))
						return (1);
				}
				if (i > 0)
					if (string[i - 1] && ft_strchr("<>", string[i - 1]))
						return (1);
			}
		}
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
int	unexpected_redirect(char **query)
{
	int	i;
	int	return_code;

	i = -1;
	return_code = 0;
	while (query[++i])
	{
		if (ft_strchr(query[i], '<') || ft_strchr(query[i], '>')
			|| ft_strchr(query[i], '|'))
		{
			if (ft_strchr(query[i], '|'))
				if (check_pipe(query[i], query, i, 0))
					return (print_token_err(ERR_TOKEN, '|', 0));
			return_code = print_redir_errors(query, i);
			if (return_code != 0)
				return (return_code);
		}
	}
	return (0);
}
