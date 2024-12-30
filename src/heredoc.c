/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:45:22 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 17:25:37 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Configures signal handlers for the heredoc process.
 *
 * This function sets up signal handling specifically for the heredoc process.
 * It catches `SIGINT` signals (which are sent when the user presses Ctrl+C)
 * and directs them to the `heredoc_sigint` function.
 * It also ignores `SIGQUIT` signals (which are sent when the user
 * presses Ctrl+\).
 */
void	signals_heredoc(void)
{
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * Handles SIGINT signal in the heredoc process.
 *
 * This function is called when the user sends a `SIGINT` signal
 * (typically by pressing Ctrl+C). It prints a newline and then calls
 * `free_child_heredoc` to clean up resources before exiting the process.
 */
void	heredoc_sigint(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	free_child_heredoc();
}

/**
 * Handles the core logic of reading input for a heredoc.
 *
 * This function manages the process of reading input for a heredoc.
 * It sets up the signal handling for the heredoc process, opens the `.heredoc`
 * file for writing, and continuously prompts the user for input using `readline`.
 * The input is written to the file until the user enters the delimiter
 * (the string marking the end of the heredoc).
 * If any `$`-prefixed variables are found in the input, they are expanded using
 * `expand_var_heredoc`.
 * If EOF (end-of-file) is reached, the `err_eof` function is called to
 * handle the error.
 */
void	helper_heredoc(char **query, char *delimiter, int file, char *buffer)
{
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
		if (ft_strrchr(buffer, '$'))
			buffer = expand_var_heredoc(buffer);
		ft_putendl_fd(buffer, file);
		free(buffer);
	}
	if (buffer)
		free(buffer);
	close(file);
}
