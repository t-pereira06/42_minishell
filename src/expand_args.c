/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:44:02 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/26 14:37:01 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

char	*get_quote_string(char *str, int pos)
{
	char	*temp;
	int		len;

	temp = 0;
	len = var_len(&str[pos + 1], '\'');
	temp = ft_substr(str, pos, len + 1);
	return (temp);
}

char	*check_variable(char *str, int pos, char *helper, char *final_expand)
{
	char	quote;
	char	*var_str;
	char	*final_str;

	quote = 0;
	pos = -1;
	var_str = 0;
	final_str = trim_before_dsign(str);
	while (str[++pos])
	{
		quote = get_quote(str[pos], quote);
		if (str[pos] == '$' && quote != '\'')
		{
			var_str = get_variable(str, pos + 1, var_len(&str[pos + 1], '$'));
			if (final_expand)
			{
				helper = ft_strdup(final_expand);
				free(final_expand);
			}
			final_expand = join_variable(helper, var_str);
			free(var_str);
		}
		else if (str[pos] == '$' && quote == '\'')
		{
			var_str = get_quote_string(str, pos);
			if (final_expand)
			{
				helper = ft_strdup(final_expand);
				free(final_expand);
			}
			final_expand = join_variable(helper, var_str);
			free(var_str);
		}
	}
	final_str = join_final_strings(final_str, final_expand);
	free(str);
	return (final_str);
}

void	check_expand_quotes(char **query)
{
	int	i;

	i = 0;
	while (query[i])
	{
		if (ft_strrchr(query[i], '$'))
			query[i] = check_variable(query[i], -1, 0, 0);
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
