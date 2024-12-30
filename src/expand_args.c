/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:44:02 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 17:21:34 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Joins two strings (`final_str` and `final_expand`) into one final string.
 *
 * This function first checks if either of the input strings is non-`NULL` and
 * appropriately joins them. It ensures memory management by freeing the
 * original strings when no longer needed.
 *
 * @param final_str The first string to join.
 * @param final_expand The second string to join.
 * @return A new string containing the concatenated result.
 */
char	*join_final_strings(char *final_str, char *final_expand)
{
	char	*helper;

	helper = 0;
	if (final_str)
	{
		helper = ft_strdup(final_str);
		free(final_str);
	}
	if (helper && final_expand)
		final_str = ft_strjoin(helper, final_expand);
	else if (!helper && final_expand)
		final_str = ft_strdup(final_expand);
	else
		final_str = ft_strdup(helper);
	free(helper);
	free(final_expand);
	return (final_str);
}

/**
 * Extracts a quoted string from the given position in the input string.
 *
 * This function finds the portion of the string enclosed in single quotes (`'`)
 * starting from the given position, and returns it as a new substring.
 *
 * @param str The string containing the quoted text.
 * @param pos The position in the string where the quote begins.
 * @return A substring containing the quoted string.
 */
char	*get_quote_string(char *str, int pos)
{
	char	*temp;
	int		len;

	temp = 0;
	len = var_len(&str[pos + 1], '\'');
	temp = ft_substr(str, pos, len + 1);
	return (temp);
}

/**
 * Processes a string to expand any variables and handle quotes.
 *
 * This function scans the input string for variables (denoted by `$`) and expands
 * them. It handles cases where variables are within quotes and builds the final
 * expanded string (`final_expand`). It returns the fully expanded string.
 *
 * @param str The string to process for variables.
 * @param pos The current position within the string.
 * @param final_expand The previously expanded string, or `NULL`.
 * @return The updated, fully expanded string.
 */
char	*check_variable(char *str, int pos, char *final_expand)
{
	char	quote;

	quote = 0;
	pos = -1;
	while (str[++pos])
	{
		quote = get_quote(str[pos], quote);
		if (str[pos] == '$' && str[pos + 1] && quote != '\'')
		{
			final_expand = get_var_wout_quote(str, pos, final_expand);
			pos += var_len(&str[pos + 1], '$');
		}
		else if (str[pos] == '$' && str[pos + 1] && (quote == '\''))
		{
			final_expand = get_var_w_quote(str, pos, final_expand);
			pos += var_len(&str[pos + 1], '$');
		}
		else
			final_expand = get_ohter_characters(str, pos, final_expand);
	}
	free(str);
	return (final_expand);
}

/**
 * Expands variables and removes quotes from the query strings.
 *
 * This function processes each string in the `query` array. It handles variable
 * expansion (for `$`) and removes quotes (both single and double quotes) from
 * the strings. It updates the `query` array in place.
 *
 * @param query The array of query strings to modify.
 */
void	check_expand_quotes(char **query)
{
	int		i;
	int		count_before;
	char	*temp;

	i = 0;
	count_before = 0;
	while (query[i])
	{
		if (ft_strrchr(query[i], '$'))
		{
			count_before = ft_dpcount(query);
			temp = ft_strdup(query[i]);
			free(query[i]);
			query[i] = check_variable(temp, -1, 0);
			if (!query[i])
			{
				remove_null_var(query, count_before, -1);
				i--;
			}
		}
		i++;
	}
	i = 0;
	while (query[i])
	{
		if (ft_strrchr(query[i], '\'') || ft_strrchr(query[i], '\"'))
			query[i] = remove_quotes(query[i]);
		i++;
	}
}
