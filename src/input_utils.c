/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:23:19 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/29 14:12:14 by tsodre-p         ###   ########.fr       */
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
int	check_op(char *operator)
{
	int	i;

	i = -1;
	while (operator[++i])
		if (ft_strchr("&;(){}*\\", operator[i]))
			return (print_op_err
				("minishell: no support for operator '", operator));
	if (check_strcmp(operator, "<") || check_strcmp(operator, ">")
		|| check_strcmp(operator, "<<") || check_strcmp(operator, ">>")
		|| check_strcmp(operator, "|"))
		return (0);
	else if (check_strcmp(operator, "||") || check_strcmp(operator, "<>")
		|| check_strcmp(operator, "<<<") || check_strcmp(operator, ">|"))
		return (print_op_err("minishell: no support for operator '", operator));
	else
		return (print_syntax_err
			("minishell: syntax error near unexpected token '", operator));
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
int	helper_operator(t_minishell *ms)
{
	int	return_val;

	return_val = check_op(ms->operator);
	free(ms->operator);
	if (return_val == 1)
		return (1);
	else
	{
		ms->operator = "\0";
		return (0);
	}
}

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
 * Checks for unexpected tokens and redirects in the input string.
 *
 * @param input The input string to check.
 * @return 0 if no unexpected tokens or redirects are found, 1 otherwise.
 */
int	unexpected_tokens(char *input)
{
	int		i;
	char	quote;
	char	**query;

	i = -1;
	quote = 0;
	query = splitter(input, ' ');
	if (unexpected_redirect(query))
		return (helper_free_dp(query), 1);
	if (query)
		helper_free_dp(query);
	return (0);
}

int	search_quote(char *query)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (query[++i])
	{
		quote = get_quote(query[i], quote);
		if (quote == query[i])
			return (1);
	}
	return (0);
}

int	check_pipe(char *string, char**query, int i)
{
	int	quote;

	quote = 0;
	quote = search_quote(string);
	if (check_strcmp(query[0], "|"))
		return (print_token_err(UNTOKEN, '|', 0));
	if (((ft_strchr(string, '|') && ft_strlen(string) > 1) && !query[i + 1] && !quote) || check_strcmp(query[0], "|"))
		return (print_token_err(UNTOKEN, '|', 0));
	//if (((check_strcmp(query[i], "|") && ft_strlen(query[i]) > 1) && !query[i + 1] && !quote) || check_strcmp(query[0], "|"))
	//return (print_token_err(UNTOKEN, '|', 0));
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
	int	quote;

	i = -1;
	quote = 0;
	while (query[++i])
	{
		if (ft_strchr(query[i], '<') || ft_strchr(query[i], '>')
			|| ft_strchr(query[i], '|'))
		{
			check_pipe(query[i], query, i);
			if (check_strcmp(query[i], "|") && !query[i + 1])
				return (print_token_err(UNTOKEN, '|', 0));
			else if (check_strcmp(query[i], "||") && !query[i + 1])
				return (print_token_err(UNTOKEN, '|', 0));
			else if (check_strcmp(query[i], ">|"))
				return (print_op_err(NOSUPPORT, ">|"));
			else if ((check_strcmp(query[i], ">>")
					|| check_strcmp(query[i], "<<")
					|| check_strcmp(query[i], ">")
					|| check_strcmp(query[i], "<")) && !query[i + 1])
				return (print_op_err(UNTOKEN, "newline"));
		}
	}
	return (0);
}
