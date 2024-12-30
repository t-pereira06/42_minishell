/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:04:06 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 17:18:30 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Checks if the given path is a directory.
 *
 * If the path is a directory, prints an error message indicating that it's
 * a directory (not a file), sets the exit status to 126, and terminates
 * the process.
 *
 * @param str The path to check.
 */
void	check_dir(char *str)
{
	DIR *dir;

	dir = opendir(str);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		g_exit_status = 126;
		free_child(NULL, 0);
		exit (g_exit_status);
	}
	closedir(dir);
}

/**
 * Checks if the provided path refers to a valid file or directory.
 *
 * If the path is a directory, it calls `check_dir`. Then, it checks if the file
 * exists and if the user has write permissions. If there are issues with access,
 * it prints an appropriate error message and terminates the process with an exit
 * status of 126 or 127.
 *
 * @param str The path to check.
 * @return 0 if successful, or exits with an error code if validation fails.
 */
int		check_if_dir_file(char *str)
{
	if ((str[0] == '.' && str[1] == '/') || str[0] == '/')
	{
		check_dir(str);
		if (access(str, F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			g_exit_status = 127;
			free_child(NULL, 0);
			exit (g_exit_status);
		}
		if (access(str, W_OK) != 0 && access(str, F_OK) == 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			g_exit_status = 126;
			free_child(NULL, 0);
			exit (g_exit_status);
		}
	}
	return (0);
}
