/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:04:06 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/29 01:05:30 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
