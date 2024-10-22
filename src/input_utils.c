/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:23:19 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/22 10:49:24 by tsodre-p         ###   ########.fr       */
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
		else if (ft_strrchr("><", input[i]) && !quote)
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
		return (print_op_err(NOSUPPORT, ">|"));
	else if (ft_strrchr("><", input[*i]) && !input[*i])
		return (print_op_err(UNTOKEN, "newline"));
	else if (ft_strrchr("><", input[*i]) && input[*i] != input[*i + 1])
		return (error_token(UNTOKEN, input[*i], 0));
	else if (ft_strrchr("><", input[*i]) && input[*i] == input[*i + 1])
		return (error_token(UNTOKEN, input[*i + 1], 1));
	return (0);
	/* em vez disto fazer apenas, se o operador for diferente dos operadores
	suportados, mandar so a mensagem a dizer que nao e suportado */
}
