/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:20:50 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/28 12:33:21 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Checks for invalid syntax in the input string.
 *
 * @param input The input string to check.
 * @return 0 if the syntax is valid, 1 otherwise.
 */
int	check_invalid_syntax(char *input)
{
	if (input[1] && input[0] == '|' && input[1] != '|')
		return (error_token(UNTOKEN, '|', 0));
	else if (input[1] && input[0] == '|' && input[1] == '|')
		return (error_token(UNTOKEN, '|', 1));
	if (input[ft_strlen(input) - 1] == '|')
	{
		ft_putstr_fd("minishell: no support for pipe prompt\n", STDERR_FILENO);
		return (1);
	}
	else if (ft_strrchr("><", input[ft_strlen(input) - 1]))
		return (print_op_err(UNTOKEN, "newline"));
	return (0);
}

int	check_op(char *operator)
{
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
 * Checks for unsupported operators and tokens in the input string.
 *
 * @param input The input string to check.
 * @return 0 if all operators and tokens are supported, 1 otherwise.
 */
int	handle_op(t_minishell *ms, char *input, int i, int j)
{
	char	quote;

	quote = 0;
	while (input[++i])
	{
		quote = get_quote(input[i], quote);
		if (ft_strchr("<>|&;(){}*\\", input[i]) && !quote)
		{
			if (j == 0)
				ms->operator = ft_strdup("\0");
			ms->temp = ft_strdup(ms->operator);
			free(ms->operator);
			ms->operator = ft_strcjoin(ms->temp, input[i]);
			free(ms->temp);
			j = 1;
		}
		else if (j == 1 && ft_strlen(ms->operator) != 0)
		{
			if (helper_operator(ms))
				return (1);
		}
	}
	helper_free_op(ms, j);
	return (unexpected_tokens(ms, input));
}

/**
 * Checks if quotes in the given input string are properly balanced.
 *
 * @param input A pointer to the input string to be checked.
 * @return Returns 0 if quotes are balanced or absent, 1 if there is
 * an unclosed quote.
 */
int	check_quotes(char *input)
{
	char	quote;

	quote = 0;
	while (*input && !quote)
	{
		if (ft_strrchr("\"\'", *input))
			quote = *input;
		input++;
	}
	while (*input && quote)
	{
		if (*input && *input == quote)
			quote = 0;
		input++;
	}
	if (*input)
		return (check_quotes(input));
	else if (!quote)
		return (0);
	else
		return (1);
}

/**
 * Checks if the input string is a valid command input.
 *
 * @param input The input string to check.
 * @return 1 if the input is valid, 0 otherwise.
 */
int	check_valid_input(t_minishell *ms, char *input)
{
	if (!input || input[0] == '\0')
		return (0);
	if (check_quotes(input))
	{
		ft_putstr_fd("minishell: unclosed quotes\n", STDERR_FILENO);
		return (0);
	}
	if (handle_op(ms, input, -1, 0))
		return (0);
	if (check_invalid_syntax(input))
		return (0);
	return (1);
}
