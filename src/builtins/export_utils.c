/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:29:44 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/10 15:53:10 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_isalnum_extra(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

void	export_err(char *str_query)
{
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(str_query, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int	valid_syntax(void)
{
	int	i;
	int	count;
	int	size;

	count = 0;
	while (ms()->query[++count])
	{
		size = 0;
		i = 0;
		if (!ft_isalpha(ms()->query[count][0]) && ms()->query[count][0] != '_')
			return (export_err(ms()->query[count]), 1);
		while (ms()->query[count][size] && ms()->query[count][size] != '=')
			size++;
		while (i < size)
		{
			if (!ft_isalnum_extra(ms()->query[count][i]))
				return (export_err(ms()->query[count]), 1);
			i++;
		}
	}
	return (0);
}
