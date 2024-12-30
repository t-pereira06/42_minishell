/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:44:10 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 17:18:41 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Opens a file for reading and sets the input file descriptor.
 *
 * Attempts to open the file specified in `query[0]` for reading. If the file
 * cannot be opened, an error is handled and returned.
 *
 * @param query The arguments containing the file path to open.
 * @return 0 if successful, or an error code if file access fails.
 */
int	do_input(char **query)
{
	ms()->in_fd = open(query[0], O_RDONLY);
	if (ms()->in_fd < 0)
		return (handle_file_acess_errors(query[0]));
	return (0);
}

/**
 * Opens a file for writing and sets the output file descriptor.
 *
 * Attempts to open the file specified in `query[0]` for reading and writing.
 * If the file cannot be opened, an error is handled and returned.
 *
 * @param query The arguments containing the file path to open.
 * @return 0 if successful, or an error code if file access fails.
 */
int	do_output(char **query)
{
	ms()->out_fd = open(query[0], O_RDWR | O_CREAT
		| O_TRUNC, S_IRUSR | S_IWUSR);
	if (ms()->out_fd < 0)
		return (handle_file_acess_errors(query[0]));
	return (0);
}

/**
 * Handles the `heredoc` functionality for input redirection.
 *
 * Ignores the SIGQUIT signal, executes the heredoc process, and opens the
 * temporary `.heredoc` file for reading. Returns an error if the file
 * doesn't exist.
 *
 * @param query The input arguments.
 * @param next  The next argument used for the heredoc delimiter.
 * @return 0 if successful, or 1 if an error occurs (e.g., file not found).
 */
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

/**
 * Opens a file for appending output and sets the output file descriptor.
 *
 * Attempts to open the file specified in `query[0]` for appending. If the file
 * cannot be opened, an error is handled and returned.
 *
 * @param query The arguments containing the file path to open.
 * @return 0 if successful, or an error code if file access fails.
 */
int	do_append(char **query)
{
	ms()->out_fd = open(query[0], O_RDWR | O_CREAT | O_APPEND,
		S_IRUSR | S_IWUSR);
	if (ms()->out_fd < 0)
		return (handle_file_acess_errors(query[0]));
	return (0);
}
