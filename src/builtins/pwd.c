/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:20:56 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/08 15:19:35 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	exit_status = 0;
	exit (0);
}
