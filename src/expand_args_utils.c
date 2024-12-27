/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:40:21 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/27 10:58:00 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*get_var_wout_quote(char *str, int pos, char *final_expand)
{
	char	*var_str;
	char	*helper;

	var_str = 0;
	helper = 0;
	var_str = get_variable(str, pos + 1, var_len(&str[pos + 1], '$'));
	if (final_expand)
	{
		helper = ft_strdup(final_expand);
		free(final_expand);
	}
	final_expand = join_variable(helper, var_str);
	free(var_str);
	return (final_expand);
}

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