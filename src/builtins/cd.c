/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:06:10 by davioliv          #+#    #+#             */
/*   Updated: 2024/11/05 12:22:49 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_cd(char **query)
{
	int	i;
	int	check;
	char	old_path[200];

	getcwd(old_path, sizeof(old_path));
	i = 0;
	while (query[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		g_exit = 1;
	}
	check = ft_dir_change(query);
	if (check != 0)
		return ;
	ft_update_env(&ms()->env, "OLDPWD", old_path);
	getcwd(old_path, sizeof(old_path));
	ft_update_env(&ms()->env, "PWD", old_path);
	g_exit = 0;
}

int	ft_dir_change(char **query)
{
	int	check;

	if (query[1])
	{
		if (ft_strlen(query[1]) == 1 && query[1][0] == '-')
		{
			printf("%s\n", get_env_info(&ms()->env, "OLDPWD"));
			check = chdir(get_env_info(&ms()->env, "OLDPWD"));
		}
		else if ((query[1][0] == '-' && query[1][1] == '-') || (ft_strlen(query[1]) == 1 && query[1][0] == '~'))
			check = chdir(get_env_info(&ms()->env, "HOME"));
		else
			check = chdir(query[1]);
	}
	else
		check = chdir(get_env_info(&ms()->env, "HOME"));
	return (check);
}
