/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:45:22 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/11/04 15:00:21 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_child_heredoc(void)
{
	/* if (cmd_query)
		ft_free_split(cmd_query);
	if (s_minishell()->pipe_fd)
		free(ms->pipe_fd);
	unlink(".heredoc");
	if (ms->paths)
		ft_free_split(ms->paths);
	if (ms->query)
		ft_free_split(ms->query);
	if (ms->args)
		ft_free_split(ms->args);
	ft_free_lst(ms->env);
	if (ms->pid)
		free(ms->pid);
	//ft_free_lst(ms->xprt);
	if (i == 1)
	{
		g_exit = 1;
		exit (1);
	} */
}

void	heredoc_sigint(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	free_child_heredoc();
}

void	err_heredoc(t_minishell *ms, char **query)
{
	ft_putstr_fd("minishell: Error creating .heredoc", STDERR_FILENO);
	free_child(ms, query, 1);
}

void	err_eof(char *str)
{
	ft_putstr_fd("minishell: warning: here-document", STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

void	helper_heredoc(t_minishell *ms, char **query, char *delimiter)
{
	int		file;
	char	*buffer;

	/*working on freeing the memory if SIGINT is called*/
	file = open(".heredoc", O_CREAT
			| O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	if (file < 0)
		err_heredoc(ms, query);
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
			/* expander here*/
		/* if (ft_strrchr(buffer, '$'))
			buffer = expander(buffer, ms); */
		ft_putendl_fd(buffer, file);
		free(buffer);
	}
	if (buffer)
		free(buffer);
	close(file);
	return (0);
}
