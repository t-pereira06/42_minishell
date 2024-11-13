/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:53:28 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/11/13 17:37:07 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Closes the file descriptors associated with the pipes used in
 * piped commands.
 *
 * @param ms The t_minishell structure containing relevant data.
 */
void	close_pipes_fd(void)
{
	int	i;

	i = 0;
	while (i < ms()->n_pipe * 2)
		close(ms()->pipe_fd[i++]);
}

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
