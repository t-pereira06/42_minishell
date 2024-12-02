/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:04:51 by davioliv          #+#    #+#             */
/*   Updated: 2024/11/05 12:23:21 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_echo(t_minishell *ms, char **query)
{
	int	i;
	int	j;

	i = 1;
	(void)ms;
	if (!(ft_strncmp(query[1], "-n", 2)))
		i++;
	while (query[i])
	{
		j = 0;
		while (query[i][j] && query[i][j] != '\n')
			printf("%c", query[i][j++]);
		if (query[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(query[1], "-n", 2))
		printf("\n");
}
