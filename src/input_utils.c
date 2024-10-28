/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:23:19 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/28 15:39:23 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
			if (((ft_strchr(query[i], '|') && ft_strlen(query[i]) > 1)
					&& (!query[i + 1])) || check_strcmp(query[0], "|"))
				return (print_token_err(UNTOKEN, '|', 0));
			else if (check_strcmp(query[i], "|") && !query[i + 1])
				return (print_token_err(UNTOKEN, '|', 0));
			if (check_strcmp(query[i], "||") && !query[i + 1])
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
