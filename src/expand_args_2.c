/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 02:52:35 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/26 02:57:44 by tsodre-p         ###   ########.fr       */
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