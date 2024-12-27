/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:20:50 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/16 13:59:23 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Checks for unsupported operators and tokens in the input string.
 *
 * @param input The input string to check.
 * @return 0 if all operators and tokens are supported, 1 otherwise.
 */
int	handle_op(char *input, int i, int j)
{
	char	quote;

	quote = 0;
	while (input[++i])
	{
		quote = get_quote(input[i], quote);
		if (ft_strchr("<>|&;(){}*\\", input[i]) && !quote)
		{
			if (j == 0)
				ms()->operator = ft_strdup("\0");
			ms()->temp = ft_strdup(ms()->operator);
			free(ms()->operator);
			ms()->operator = ft_strcjoin(ms()->temp, input[i]);
			free(ms()->temp);
			j = 1;
		}
		else if (j == 1 && ft_strlen(ms()->operator) != 0)
		{
			if (helper_operator(&input[i + 1], i - 1))
				return (1);
			j = 0;
		}
	}
	helper_free_op(j);
	return (unexpected_tokens(input));
}

/**
 * Checks for unexpected tokens and redirects in the input string.
 *
 * @param input The input string to check.
 * @return 0 if no unexpected tokens or redirects are found, 1 otherwise.
 */
int	unexpected_tokens(char *input)
{
	char	**query;
	//int		i;
	//char	quote;
	//i = -1;
	//quote = 0;
	query = splitter(input, ' ');
	if (unexpected_redirect(query))
		return (helper_free_dp(query), 1);
	if (query)
		helper_free_dp(query);
	return (0);
}

/**
 * Checks if the input string is a valid command input.
 *
 * @param input The input string to check.
 * @return 1 if the input is valid, 0 otherwise.
 */
int	check_valid_input(char *input)
{
	char	*temp;
	char	*temp2;

	if (!input || input[0] == '\0')
		return (0);
	if (check_quotes(input))
	{
		ft_putstr_fd("minishell: unclosed quotes\n", STDERR_FILENO);
		return (0);
	}
	temp2 = ft_strdup(input);
	temp = ft_strdup(temp2);
	free(temp2);
	temp2 = ft_strcjoin(temp, ' ');
	free(temp);
	if (handle_op(temp2, -1, 0))
		return (free(temp2), 0);
	free(temp2);
	return (1);
}
