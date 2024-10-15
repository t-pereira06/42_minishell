/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davioliv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:04:51 by davioliv          #+#    #+#             */
/*   Updated: 2024/10/14 20:19:19 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	j;

	i = 1;
	if (!(ft_strncmp(args[1], "-n", 2)))
		i++;
	while (args[i])
	{
		j = 0;
		while (args[i][j] && args[i][j] != '\n')
			printf("%c", args[i][j++]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(args[1], "-n", 2))
		printf("\n");
}
