/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:06:10 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/03 00:30:38 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_cd(char *arg)
{
	int	check;
	char	old_path[200];

	getcwd(old_path, sizeof(old_path));
	check = ft_dir_change(arg);
	if (check != 0)
		return ;
	ft_update_env(&ms()->env, "OLDPWD", old_path);
	getcwd(old_path, sizeof(old_path));
	ft_update_env(&ms()->env, "PWD", old_path);
	g_exit = 0;
}

int	ft_dir_change(char *arg)
{
	int	check;

	if (arg)
	{
		if (ft_strlen(arg) == 1 && arg[0] == '-')
		{
			printf("%s\n", get_env_info(&ms()->env, "OLDPWD"));
			check = chdir(get_env_info(&ms()->env, "OLDPWD"));
		}
		else if (ft_strcmp(arg, "--")
				|| (ft_strlen(arg) == 1 && arg[0] == '~'))
			check = chdir(get_env_info(&ms()->env, "HOME"));
		else
			check = chdir(arg);
	}
	else
		check = chdir(get_env_info(&ms()->env, "HOME"));
	return (check);
}

void	exec_cd(void)
{
	int		count;
	int		child_status;

	count = ft_dpcount(ms()->query);
	wait(&child_status);
	if (WIFEXITED(child_status))
		g_exit = WEXITSTATUS(child_status);
	if (g_exit == 0)
	{
		if (count == 1)
			ft_cd(NULL);
		else if (count == 2)
			ft_cd(ms()->query[1]);
		else
		{
			ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
			g_exit = 1;
		}
		
	}
}
