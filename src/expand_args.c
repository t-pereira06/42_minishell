/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:44:02 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/25 23:48:48 by tsodre-p         ###   ########.fr       */
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

char	*check_variable(char *str, int pos, int in)
{
	//missing when trying to expand $?
	//fix when trying $HOMEola$HOME
	char	quote;
	char	*str1;
	char	*str2;
	char	*final_str;

	quote = 0;
	pos = -1;
	while (str[++pos])
	{
		quote = get_quote(str[pos], quote);
		if (str[pos] == '$' && quote != '\'')
		{
			if (in == 0)
				str1 = ft_substr(str, 0, pos);
			else
				str1 = ft_substr(final_str, 0, ft_strlen(final_str));
			str2 = get_variable(str, pos + 1, var_len(&str[pos + 1]));
			pos += var_len(&str[pos + 1]);
			if (in == 0)
				final_str = ft_strjoin(str1, str2);
			else
			{
				free(final_str);
				final_str = ft_strjoin(str1, str2);
			}
			in++;
			free(str2);
			free(str1);
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
			query[i] = check_variable(query[i], -1, 0);
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
