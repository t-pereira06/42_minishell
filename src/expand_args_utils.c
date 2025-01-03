/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:40:21 by tsodre-p          #+#    #+#             */
/*   Updated: 2025/01/03 09:22:51 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Retrieves the value of a variable without quotes and expands it.
 *
 * This function extracts the variable starting at a given position, checks for
 * specific conditions like `"$"`, and joins the variable's value with any
 * previously expanded string (`final_expand`). The result is returned as
 * a new string.
 *
 * @param str The string containing the variable.
 * @param pos The position where the variable starts.
 * @param final_expand The previously expanded string, or `NULL`.
 * @return A new string containing the expanded variable.
 */
char	*get_var_wout_quote(char *str, int pos, char *final_expand)
{
	char	*var_str;
	char	*helper;

	var_str = 0;
	helper = 0;
	var_str = get_variable(str, pos + 1, var_len(&str[pos + 1], '$'));
	if (match_strings(str, "\"$\""))
		var_str = ft_strdup("$\0");
	if (final_expand)
	{
		helper = ft_strdup(final_expand);
		free(final_expand);
	}
	final_expand = join_variable(helper, var_str);
	free(var_str);
	return (final_expand);
}

/**
 * Retrieves the value of a variable with quotes and expands it.
 *
 * This function extracts a quoted string (if any) starting at a given
 * position and joins it with any previously expanded string
 * (`final_expand`).
 *
 * The result is returned as a new string.
 *
 * @param str The string containing the variable.
 * @param pos The position where the quoted string starts.
 * @param final_expand The previously expanded string, or `NULL`.
 * @return A new string containing the expanded quoted variable.
 */
char	*get_var_w_quote(char *str, int pos, char *final_expand)
{
	char	*var_str;
	char	*helper;

	var_str = 0;
	helper = 0;
	var_str = get_quote_string(str, pos);
	if (final_expand)
	{
		helper = ft_strdup(final_expand);
		free(final_expand);
	}
	final_expand = join_variable(helper, var_str);
	free(var_str);
	return (final_expand);
}

/**
 * Adds a character to the expanded string.
 *
 * This function appends a character from the original string (`str[pos]`) to the
 * previously expanded string (`final_expand`), and returns the updated string.
 *
 * @param str The original string.
 * @param pos The position of the character to append.
 * @param final_expand The previously expanded string, or `NULL`.
 * @return A new string with the added character.
 */
char	*get_ohter_characters(char *str, int pos, char *final_expand)
{
	char	*temp;

	temp = 0;
	if (final_expand)
	{
		temp = ft_strcjoin(final_expand, str[pos]);
		free(final_expand);
		final_expand = ft_strdup(temp);
		free(temp);
	}
	else
	{
		temp = (char *)malloc(sizeof(char) * (1 + 1));
		temp[0] = str[pos];
		temp[1] = '\0';
		final_expand = ft_strdup(temp);
		free(temp);
	}
	return (final_expand);
}

/**
 * Removes `NULL` values from the query array and compacts it.
 *
 * This function filters out `NULL` entries from the `query` array and reorders
 * it, preserving the non-`NULL` entries. The array is updated in place.
 *
 * @param query The query array to modify.
 * @param count_before The number of entries in the array before modification.
 * @param j The index used during the removal process.
 */
void	remove_null_var(char **query, int count_before, int j)
{
	int		a;
	char	**temp_query;

	a = 0;
	temp_query = ft_dpdup(query, count_before);
	while (++j < count_before)
	{
		free(query[j]);
		query[j] = NULL;
	}
	j = 0;
	while (j < count_before)
	{
		if (temp_query[j] != NULL)
		{
			query[a] = ft_strdup(temp_query[j]);
			a++;
		}
		j++;
	}
	j = -1;
	while (++j < count_before)
		free(temp_query[j]);
	free(temp_query);
}
