/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:44:10 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 15:30:53 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	do_input(char **query)
{
	ms()->in_fd = open(query[0], O_RDONLY);
	if (ms()->in_fd < 0)
		return (handle_file_acess_errors(query[0]));
	return (0);
}

int	do_output(char **query)
{
	ms()->out_fd = open(query[0], O_RDWR | O_CREAT
		| O_TRUNC, S_IRUSR | S_IWUSR);
	if (ms()->out_fd < 0)
		return (handle_file_acess_errors(query[0]));
	return (0);
}

int	do_heredoc(char **query, char **next)
{
	signal(SIGQUIT, SIG_IGN);
	helper_heredoc(query, next[0], 0, 0);
	ms()->in_fd = open(".heredoc", O_RDONLY);
	if (ms()->in_fd < 0)
	{
		return (ft_putstr_fd("minishell: .heredoc: No such file or directory\n",
				STDERR_FILENO), 1);
	}
	return (0);
}

int	do_append(char **query)
{
	ms()->out_fd = open(query[0], O_RDWR | O_CREAT | O_APPEND,
		S_IRUSR | S_IWUSR);
	if (ms()->out_fd < 0)
		return (handle_file_acess_errors(query[0]));
	return (0);
}
