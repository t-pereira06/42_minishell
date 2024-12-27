/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:54:06 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/27 11:54:31 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

char	*expand_var_heredoc(char *buffer)
{
	char	*temp;

	temp = ft_strtrim(buffer, "\"");
	free(buffer);
	buffer = check_variable(temp, -1, 0);
	return (buffer);
}
