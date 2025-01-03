/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:54:06 by tsodre-p          #+#    #+#             */
/*   Updated: 2025/01/03 09:24:02 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Handles errors during the creation of the heredoc file.
 *
 * This function prints an error message to the standard error stream when
 * a problem occurs while creating the `.heredoc` file.
 *
 * Afterward, it frees resources associated with the given query and
 * exits the child process.
 */
void	err_heredoc(char **query)
{
	ft_putstr_fd("minishell: Error creating .heredoc", STDERR_FILENO);
	free_child(query, 1);
}

/**
 * Handles EOF (end-of-file) errors in a heredoc.
 *
 * This function prints a warning message to indicate that the heredoc input
 * was prematurely terminated by EOF (end-of-file) rather than the expected
 * delimiter.
 *
 * The warning includes the delimiter string that was expected.
 */
void	err_eof(char *str)
{
	ft_putstr_fd("minishell: warning: here-document", STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

/**
 * Expands variables in a heredoc buffer.
 *
 * This function trims any surrounding double quotes from the provided `buffer`
 * string, then processes it to expand any variables within the string
 * (e.g., `$`-prefixed variables).
 *
 * The modified buffer with expanded variables is returned.
 */
char	*expand_var_heredoc(char *buffer)
{
	char	*temp;

	temp = ft_strtrim(buffer, "\"");
	free(buffer);
	buffer = check_variable(temp, -1, 0);
	return (buffer);
}
