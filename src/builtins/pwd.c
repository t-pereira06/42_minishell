/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:20:56 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/10 15:30:12 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_pwd(void)
{
	char	*temp;

	if (ft_strlen(ms()->args[0]) > 4)
	{
		printf("no options allowed");
		free_child(NULL, 1);
	}
	temp = getcwd(0, 0);
	printf("%s\n", temp);
	free_child(NULL, 0);
	g_exit_status = 0;
	exit (0);
}
