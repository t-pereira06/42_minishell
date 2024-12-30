/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 02:52:35 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 17:22:12 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Calculates the length of a variable name in a string.
 *
 * Iterates through the string until a specified character (`c`), space,
 * or quote is found, and returns the length of the variable name.
 *
 * @param str The string containing the variable.
 * @param c The character that marks the end of the variable name.
 * @return The length of the variable name.
 */
int	var_len(char *str, char c)
{
	int	pos;
	int	len;

	pos = -1;
	len = 0;
	while (str[++pos])
	{
		if (ft_chrcmp(str[pos], c) || ft_chrcmp(str[pos], ' ')
			|| ft_chrcmp(str[pos], '\"') || ft_chrcmp(str[pos], '\''))
			return (len);
		len++;
	}
	return (len);
}

/**
 * Retrieves the exit status as a string, prepended to a variable name.
 *
 * If the variable starts with a `$`, it extracts the exit
 * status (`g_exit_status`),
 * joins it with the variable's content, and returns the resulting string.
 *
 * @param var_name The variable name, starting with `$`.
 * @return A new string representing the exit status and variable content.
 */
char	*get_es_string(char *var_name)
{
	char	*temp;
	char	*new_str;
	char	*str_es;

	temp = ft_substr(var_name, 1, ft_strlen(var_name));
	if (temp)
	{
		str_es = ft_itoa(g_exit_status);
		new_str = ft_strjoin(str_es, temp);
		free(temp);
		free(str_es);
		return (new_str);
	}
	new_str = ft_itoa(g_exit_status);
	return (new_str);
}

/**
 * Retrieves the value of an environment variable or exit status.
 *
 * Extracts the variable name from the string, looks it up in the environment,
 * and returns its value. If the variable is `$?`, the exit status is returned.
 *
 * @param str The string containing the variable.
 * @param pos The position where the variable starts.
 * @param size The length of the variable name.
 * @return The value of the variable or exit status as a string.
 */
char	*get_variable(char *str, int pos, int size)
{
	char	*var_info;
	char	*var_name;

	var_name = ft_substr(str, pos, size);
	var_info = get_env_info(&ms()->env, var_name);
	if (var_info)
	{
		var_info = ft_substr(get_env_info(&ms()->env, var_name), 0,
				ft_strlen(get_env_info(&ms()->env, var_name)));
		free(var_name);
		return (var_info);
	}
	else
	{
		if (ft_chrcmp(var_name[0], '?'))
		{
			var_info = get_es_string(var_name);
			return (free(var_name), var_info);
		}
		free(var_name);
		return (var_info);
	}
}

/**
 * Joins two strings, handling variable values.
 *
 * Combines the string before the variable and the variable string. If the
 * variable string is `NULL`, the function returns the original string.
 *
 * @param before_var The string before the variable.
 * @param var_str The variable string to join.
 * @return A new string representing the combined result.
 */
char	*join_variable(char *before_var, char *var_str)
{
	char	*final_str;

	final_str = 0;
	if (var_str != NULL)
	{
		if (before_var != NULL)
			final_str = ft_strjoin(before_var, var_str);
		else
		{
			free(final_str);
			final_str = ft_strdup(var_str);
		}
		free(before_var);
		return (final_str);
	}
	if (before_var)
		return (before_var);
	return (NULL);
}

/**
 * Trims the string before a dollar sign (`$`).
 *
 * Scans the string for a dollar sign outside of quotes and returns
 * the substring before the dollar sign.
 *
 * @param str The string to scan.
 * @return The substring before the dollar sign, or `NULL` if no
 * dollar sign is found.
 */
char	*trim_before_dsign(char *str)
{
	int		pos;
	char	quote;

	pos = -1;
	quote = 0;
	while (str[++pos])
	{
		quote = get_quote(str[pos], quote);
		if (str[pos] == '$' && quote != '\'')
			return (ft_substr(str, 0, pos));
		if (str[pos] == '$' && quote == '\'')
			return (ft_substr(str, 0, pos));
	}
	return (NULL);
}
