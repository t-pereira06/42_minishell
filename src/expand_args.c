/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:44:02 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/26 02:51:21 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	var_len(char *str)
{
	int	pos;
	int	len;

	pos = -1;
	len = 0;
	while (str[++pos])
	{
		if (ft_chrcmp(str[pos], '$'))
			return (len);
		len++;
	}
	return (len);
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
		return (final_str);
	}
	return (NULL);
}

char	*check_variable(char *str, int pos)
{
	//missing when trying to expand $?
	//fix when trying $HOMEola$HOME
	char	quote;
	char	*before_var;
	char	*var_str;
	char	*final_str;

	quote = 0;
	pos = -1;
	before_var = 0;
	final_str = 0;
	var_str = 0;
	while (str[++pos])
	{
		quote = get_quote(str[pos], quote);
		if (str[pos] == '$' && quote != '\'')
		{
			var_str = get_variable(str, pos + 1, var_len(&str[pos + 1]));
			if (final_str)
			{
				before_var = ft_strdup(final_str);
				free(final_str);
			}
			final_str = join_variable(before_var, var_str);
			free(before_var);
			free(var_str);
		}
	}
	free(str);
	return(final_str);
}

void	check_expand_quotes(char **query)
{
	int	i;

	i = 0;
	while (query[i])
	{
		if (ft_strrchr(query[i], '$'))
			query[i] = check_variable(query[i], -1);
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
