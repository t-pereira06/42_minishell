/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:44:02 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/26 02:57:27 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*check_variable(char *str, int pos)
{
	//missing when trying to expand $?
	//fix when trying $HOMEola$HOME
	char	quote;
	char	*helper;
	char	*var_str;
	char	*final_expand;
	char	*final_str;

	quote = 0;
	pos = -1;
	helper = 0;
	final_expand = 0;
	var_str = 0;
	while (str[++pos])
	{
		quote = get_quote(str[pos], quote);
		if (str[pos] == '$' && quote != '\'')
		{
			var_str = get_variable(str, pos + 1, var_len(&str[pos + 1]));
			if (final_expand)
			{
				helper = ft_strdup(final_expand);
				free(final_expand);
			}
			final_expand = join_variable(helper, var_str);
			free(helper);
			free(var_str);
		}
	}
	free(str);
	helper = ft_strdup(final_str);
	free(final_str);
	final_str = ft_strjoin(helper, final_expand);
	free(helper);
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
