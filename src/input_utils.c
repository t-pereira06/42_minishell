/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:23:19 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/28 12:36:30 by tsodre-p         ###   ########.fr       */
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
 * Frees the operator in the minishell structure if it has been set.
 *
 * @param ms Pointer to the minishell structure containing the operator
 * to be freed.
 * @param j An integer flag indicating if the operator has
 * been used (1 if true).
 *
 * Frees the memory allocated for `ms->operator` and sets it to `NULL` if
 * `j` is 1 and `ms->operator` is not empty. This prevents memory leaks by
 * ensuring that `ms->operator` is only freed when necessary.
 */
void	helper_free_op(t_minishell *ms, int j)
{
	if (j == 1 && *ms->operator != '\0')
	{
		free(ms->operator);
		ms->operator = NULL;
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
int	unexpected_tokens(t_minishell *ms, char *input)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	(void)ms;
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
