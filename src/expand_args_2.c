/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 02:52:35 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/27 14:24:58 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

char	*get_variable(char *str, int pos, int size)
{
	char	*var_info;
	char	*var_name;

	var_name = ft_substr(str, pos, size);
	var_info = get_env_info(&ms()->env, var_name);
	if (var_info)
	{
		var_info = ft_substr(get_env_info(&ms()->env, var_name), 0 ,
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
