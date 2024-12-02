/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:10:19 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/02 20:54:23 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(void)
{
	ft_putstr_fd(ms()->args[0], STDERR_FILENO);
	if (ft_strlen(ms()->args[0]) > 5)
	{
		printf("no options allowed");
		free_child(NULL, 1);
	}
	free_child(NULL, 0);
	g_exit = 0;
	exit (0);
	//still working on this one
}
