/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:44:10 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/23 15:16:00 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	change_fds(t_minishell *ms)
{
	dup2(ms->in_fd, STDIN_FILENO);
	dup2(ms->out_fd, STDOUT_FILENO);
}

int	do_input(t_minishell *ms, char **query)
{
	ms->in_fd = open(query[0], O_RDONLY);
	if (ms->in_fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(query[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	do_output(t_minishell *ms, char **query)
{
	ms->out_fd = open(query[0], O_RDWR | O_CREAT
			| O_TRUNC, S_IRUSR | S_IWUSR);
	if (ms->out_fd < 0)
		return (ft_putstr_fd("Error creating file\n", STDERR_FILENO), 1);
	return (0);
}

int	do_append(t_minishell *ms, char **query)
{
	ms->out_fd = open(query[0], O_RDWR | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR);
	if (ms->out_fd < 0)
		return (ft_putstr_fd("Error creating file\n", STDERR_FILENO), 1);
	return (0);
}
