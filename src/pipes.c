/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:53:28 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/11/12 21:01:44 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Creates multiple pipes for inter-process communication.
 *
 * @param ms The minishell structure.
 */
void	do_pipex(void)
{
	int	i;

	i = 0;
	while (i < ms()->n_pipe)
	{
		if (pipe(ms()->pipe_fd + (i * 2)) < 0)
		{
			ft_putstr_fd(ERR_PIPE, STDERR_FILENO);
			free_child(NULL, 1);
		}
		i++;
	}
}
