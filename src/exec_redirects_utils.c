/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:48:52 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 17:17:04 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Changes the standard input and output file descriptors.
 *
 * Redirects the `STDIN_FILENO` and `STDOUT_FILENO` to the file descriptors
 * specified in `ms()->in_fd` and `ms()->out_fd`, respectively.
 */
void	change_fds(void)
{
	dup2(ms()->in_fd, STDIN_FILENO);
	dup2(ms()->out_fd, STDOUT_FILENO);
}

/**
 * Handles errors related to file access permissions.
 *
 * Checks if the specified file exists and if the user has the necessary
 * write permissions. Prints an error message depending on the type of error
 * (file not found, permission denied, or file creation error) and returns 1
 * to indicate failure.
 *
 * @param str The file path to check.
 * @return 1 if an error occurs, 0 otherwise.
 */
int	handle_file_acess_errors(char *str)
{
	if (access(str, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	else if (access(str, W_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		return (1);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Error creating file\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
