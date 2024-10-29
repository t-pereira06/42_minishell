/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:38:13 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/29 11:42:06 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	len_quoteless(char *arg)
{
	int		i;
	int		len;
	char	quote;

	i = -1;
	quote = 0;
	len = 0;
	while (arg[++i])
	{
		if (ft_strchr("\"\'", arg[i]) && !quote)
		{
			quote = arg[i];
			len--;
		}
		else if (ft_strchr("\"\'", arg[i]) && quote == arg[i])
		{
			len--;
			quote = 0;
		}
		len++;
	}
	return (len);
}

void	find_quote(char *arg, int *i, char *quote)
{
	if (ft_strchr("\"\'", arg[*i]) && !*quote)
		*quote = arg[*i];
	else if (ft_strchr("\"\'", arg[*i]) && *quote == arg[*i])
		*quote = 0;
}

char	*remove_quotes(char *arg)
{
	char	*res;
	char	quote;
	int		i;
	int		j;

	i = -1;
	j = 0;
	quote = 0;
	if (len_quoteless(arg) <= 0)
	{
		free(arg);
		return (ft_strdup(""));
	}
	res = ft_calloc(len_quoteless(arg) + 1, sizeof(char));
	while (arg[++i])
	{
		find_quote(arg, &i, &quote);
		if (i > (int)ft_strlen(arg) - 1)
			break ;
		if ((quote && quote != arg[i]) || (!quote && !ft_strchr("\"\'", arg[i])))
			res[j++] = arg[i];
	}
	return (res[j] = 0, free(arg), res);
}
