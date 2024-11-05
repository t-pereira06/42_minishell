/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:44:02 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/11/05 12:16:48 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	check_expand(char **query)
{
	int	i;

	i = -1;
	while (query[++i])
		if (ft_strrchr(query[i], '\'') || ft_strrchr(query[i], '\"'))
			query[i] = remove_quotes(query[i]);
}
