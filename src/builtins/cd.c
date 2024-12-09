/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:06:10 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/09 14:43:14 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	cd_error_handler(void)
{
	struct stat	statbuf;

	if (stat(ms()->query[1], &statbuf) == 0)
		return (0);
	else if (ms()->query[1][0] == '-' && ft_strlen(ms()->query[1]) != 1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(ms()->query[1], STDERR_FILENO);
		ft_putstr_fd(": Invalid option\n", STDERR_FILENO);
		return (1);
	}
	else if (!ft_strcmp(ms()->query[1], "-"))
	{
		if (!get_env_info(&ms()->env, "OLDPWD"))
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n",
					STDERR_FILENO), 1);
	}
	return (0);
}

void	change_env_exp_var(char *env_var)
{
	char	*cwd;
	char	*var;
	char	*temp;

	cwd = getcwd(0, 0);
	var = ft_strcjoin(env_var, '=');
	temp = ft_strjoin(var, cwd);
	ft_update_env(ms()->env, env_var, temp);
	//export here
	//ft_update_exp(ms()->export, "env_var", temp);
	free(cwd);
	free(var);
	free(temp);
}

void	ft_cd(char *arg)
{
	if (arg && !ft_strcmp(arg, "-"))
	{
		ft_putstr_fd(get_env_info(&ms()->env, "OLDPWD"), STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(ms()->query[1]);
		ms()->query[1] = ft_strdup(get_env_info(&ms()->env, "OLDPWD"));
	}
	else if (arg && !ft_strcmp(arg, "~"))
	{
		free(ms()->query[1]);
		ms()->query[1] = ft_strdup(get_env_info(&ms()->env, "HOME"));
	}
	change_env_exp_var("OLDPWD");
	if (!arg)
		chdir(get_env_info(&ms()->env, "HOME"));
	else
		chdir(ms()->query[1]);
	change_env_exp_var("PWD");
}

void	exec_cd_child(void)
{
	if (ft_dpcount(ms()->query) == 1)
	{
		free_child(NULL, 0);
		exit(g_exit_status);
	}
	if (ft_dpcount(ms()->query) > 2)
	{
		ft_putstr_fd("minishell: too many arguments\n", STDERR_FILENO);
		free_child(NULL, 1);
		exit(g_exit_status);
	}
	else
	{
		g_exit_status = cd_error_handler();
		free_child(NULL, g_exit_status);
		exit(g_exit_status);
	}
}

void	exec_cd(void)
{
	int		count;
	int		child_status;

	count = ft_dpcount(ms()->query);
	wait(&child_status);
	if (WIFEXITED(child_status))
		g_exit_status = WEXITSTATUS(child_status);
	if (g_exit_status == 0)
	{
		if (count == 1)
			ft_cd(NULL);
		else if (count == 2)
			ft_cd(ms()->query[1]);
	}
}
