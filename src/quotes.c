/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:38:13 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 15:42:23 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

void	find_quote(char *arg, int *i, char *quote)
{
	if (ft_strchr("\"\'", arg[*i]) && !*quote)
		*quote = arg[*i];
	else if (ft_strchr("\"\'", arg[*i]) && *quote == arg[*i])
		*quote = 0;
}

char	*remove_quotes(char *arg)
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
