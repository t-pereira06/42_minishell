/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:06:10 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/08 19:26:31 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
		exit_status = 0;
		free_child(NULL, 0);
		exit(exit_status);
	}
	if (ft_dpcount(ms()->query) > 2)
	{
		ft_putstr_fd("minishell: too many arguments\n", STDERR_FILENO);
		exit_status = 1;
		free_child(NULL, 0);
		exit(exit_status);
	}
	else
	{
		exit_status = 0;
		free_child(NULL, 0);
		exit(exit_status);
		//check_errors(ms, cmd_query);
	}
}

void	exec_cd(void)
{
	int		count;
	int		child_status;

	count = ft_dpcount(ms()->query);
	wait(&child_status);
	if (WIFEXITED(child_status))
		exit_status = WEXITSTATUS(child_status);
	if (exit_status == 0)
	{
		if (count == 1)
			ft_cd(NULL);
		else if (count == 2)
			ft_cd(ms()->query[1]);
	}
}
