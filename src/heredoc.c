/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:45:22 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/09 14:21:03 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	signals_heredoc(void)
{
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_sigint(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	free_child_heredoc();
}

void	err_heredoc(char **query)
{
	ft_putstr_fd("minishell: Error creating .heredoc", STDERR_FILENO);
	free_child(query, 1);
}

void	err_eof(char *str)
{
	ft_putstr_fd("minishell: warning: here-document", STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

void	helper_heredoc(char **query, char *delimiter)
{
	int		file;
	char	*buffer;

	signals_heredoc();
	file = open(".heredoc", O_CREAT
			| O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	if (file < 0)
		err_heredoc(query);
	while (1)
	{
		buffer = readline(">");
		if (!buffer)
		{
			err_eof(delimiter);
			break ;
		}
		if (!ft_strncmp(delimiter, buffer, ft_strlen(delimiter) + 1))
			break ;
			/* expander here */
		/* if (ft_strrchr(buffer, '$'))
			buffer = expander(buffer); */
		ft_putendl_fd(buffer, file);
		free(buffer);
	}
	if (buffer)
		free(buffer);
	close(file);
}
