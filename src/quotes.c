/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:38:13 by tsodre-p          #+#    #+#             */
/*   Updated: 2025/01/02 18:01:47 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Calculates the length of a string excluding any quotes.
 *
 * This function iterates through the string and counts the number of
 * characters, skipping over quoted characters, effectively excluding content
 * inside quotes.
 *
 * @param arg The input string.
 * @return The length of the string without quotes.
 */
int	len_quoteless(char *arg)
{
	int		i;
	int		len;
	char	quote;

	i = -1;
	quote = 0;
	len = 0;
	while (arg[++i])
	{
		if (ft_strchr("\"\'", arg[i]) && !quote)
		{
			quote = arg[i];
			len--;
		}
		else if (ft_strchr("\"\'", arg[i]) && quote == arg[i])
		{
			len--;
			quote = 0;
		}
		len++;
	}
	return (len);
}

/**
 * Checks for and toggles quotes in the string.
 *
 * This function identifies whether the current character in the string opens
 * or closes a quote and updates the provided `quote` variable accordingly.
 *
 * @param arg The input string.
 * @param i The current index in the string.
 * @param quote The current quote type (single or double).
 */
void	find_quote(char *arg, int *i, char *quote)
{
	if (ft_strchr("\"\'", arg[*i]) && !*quote)
		*quote = arg[*i];
	else if (ft_strchr("\"\'", arg[*i]) && *quote == arg[*i])
		*quote = 0;
}

/**
 * Removes quotes from a string.
 *
 * This function removes both single and double quotes from the string,
 * preserving the content inside the quotes. It returns a new string
 * without any quotes.
 *
 * @param arg The input string with quotes.
 * @return A new string with quotes removed.
 */
char	*trim_quotes(char *arg)
{
	char	*res;
	char	quote;
	int		i;
	int		j;

	i = -1;
	j = 0;
	quote = 0;
	if (len_quoteless(arg) <= 0)
	{
		free(arg);
		return (ft_strdup(""));
	}
	res = ft_calloc(len_quoteless(arg) + 1, sizeof(char));
	while (arg[++i])
	{
		find_quote(arg, &i, &quote);
		if (i > (int)ft_strlen(arg) - 1)
			break ;
		if ((quote && quote != arg[i])
			|| (!quote && !ft_strchr("\"\'", arg[i])))
			res[j++] = arg[i];
	}
	return (res[j] = 0, free(arg), res);
}

/**
 * Checks if the quotes in the given input string are properly paired.
 *
 * This function scans the input string and ensures that each opening quote
 * (either single or double) has a corresponding closing quote.
 *
 * It returns 0  if the quotes are balanced or if there are no quotes,
 * and 1 if there is an unclosed quote at the end of the string.
 *
 * @param input A pointer to the input string to be checked.
 * @return Returns 0 if quotes are balanced or absent, 1 if there is
 * an unclosed quote.
 */
int	are_quotes_balanced(char *input)
{
	char	quote;

	quote = 0;
	while (*input)
	{
		if (!quote && ft_strrchr("\"\'", *input))
			quote = *input;
		else if (quote && *input == quote)
			quote = 0;
		input++;
	}
	return (quote);
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
