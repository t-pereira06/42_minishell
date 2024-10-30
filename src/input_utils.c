/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:23:19 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/30 11:45:59 by tsodre-p         ###   ########.fr       */
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
int	check_op(char *operator, char *input)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (operator[++i])
		if (ft_strchr("&;(){}*\\", operator[i]))
			return (print_op_err(ERR_OP, operator));
	if (check_strcmp(operator, "<") || check_strcmp(operator, ">")
		|| check_strcmp(operator, "<<") || check_strcmp(operator, ">>")
		|| check_strcmp(operator, "|"))
	{
		while (input[j] == ' ')
			j++;
		if (input[j] == '<' || input[j] == '>')
			return (print_syntax_err(ERR_TOKEN, operator));
		else
			return (0);
	}
	else if (check_strcmp(operator, "||") || check_strcmp(operator, "<>")
		|| check_strcmp(operator, "<<<") || check_strcmp(operator, ">|"))
		return (print_op_err(ERR_OP, operator));
	else
		return (print_syntax_err(ERR_TOKEN, operator));
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
int	helper_operator(t_minishell *ms, char *input)
{
	int	return_val;

	return_val = check_op(ms->operator, input);
	free(ms->operator);
	if (return_val == 1)
		return (1);
	else
	{
		ms->operator = "\0";
		return (0);
	}
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

int	check_pipe(char *string, char**query, int a, int quote)
{
	int	i;

	i = -1;
	if (check_strcmp(query[0], "|")
		|| (check_strcmp(query[0], "|") && (!query[a - 1] || !query[a + 1])))
		return (1);
	if (check_strcmp(query[a], "|")
		&& ft_strchr("<>", query[a - 1][ft_strlen(query[a - 1]) - 1]))
		return (1);
	else if (ft_strchr(string, '|') && ft_strlen(string) > 1 && !query[a + 1])
	{
		while (string[++i])
		{
			quote = get_quote(string[i], quote);
			if (string[i] == '|' && !quote)
			{
				if ((i == 0 || !string[i - 1])
					|| (i + 1 >= (int)ft_strlen(string) || !string[i + 1]))
					return (1);
				if (ft_strchr("<>", string[i - 1]))
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

	i = -1;
	while (query[++i])
	{
		if (ft_strchr(query[i], '<') || ft_strchr(query[i], '>')
			|| ft_strchr(query[i], '|'))
		{
			if (check_pipe(query[i], query, i, 0))
				return (print_token_err(ERR_TOKEN, '|', 0));
			if (check_strcmp(query[i], "|") && !query[i + 1])
				return (print_token_err(ERR_TOKEN, '|', 0));
			else if (check_strcmp(query[i], "||") && !query[i + 1])
				return (print_token_err(ERR_TOKEN, '|', 0));
			else if (check_strcmp(query[i], ">|"))
				return (print_op_err(ERR_OP, ">|"));
			else if ((check_strcmp(query[i], ">>")
					|| check_strcmp(query[i], "<<")
					|| check_strcmp(query[i], ">")
					|| check_strcmp(query[i], "<")) && !query[i + 1])
				return (print_op_err(ERR_TOKEN, "newline"));
		}
	}
	return (0);
}
