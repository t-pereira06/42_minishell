/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:44:02 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/29 01:15:59 by tsodre-p         ###   ########.fr       */
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
					remove_null_var(query, count_before, -1);
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
