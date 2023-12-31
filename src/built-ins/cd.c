/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:42:56 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/28 12:57:29 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Get the home directory path.
 *
 * @param ms   A pointer to the t_minishell struct.
 * @param arg  The argument string.
 * @return     The combined path string.
 */
static char	*get_home(t_minishell *ms, char *arg)
{
	char	*new;
	char	*temp;

	temp = get_env_info(&ms->env, "HOME");
	new = ft_strjoin(temp, arg + 1);
	return (new);
}

/**
 * Execute the cd command.
 *
 * @param ms    A pointer to the t_minishell struct.
 * @param path  The path to change the directory to.
 */
static void	execute_cd(t_minishell *ms, char *path)
{
	char	*old_pwd;
	char	*new_path;
	char	*temp;
	char	*new_pwd;

	if (path[0] == '~')
		new_path = get_home(ms, path);
	else if (path[0] == '-')
		new_path = ft_strdup(get_env_info(&ms->env, "OLDPWD"));
	else
		new_path = ft_strdup(path);
	temp = getcwd(0, 0);
	old_pwd = ft_strjoin("OLDPWD=", temp);
	free(temp);
	update_info(ms->env, "OLDPWD", old_pwd);
	update_export(ms->xprt, "OLDPWD", old_pwd);
	chdir(new_path);
	free(new_path);
	temp = getcwd(0, 0);
	new_pwd = ft_strjoin("PWD=", temp);
	free(temp);
	update_info(ms->env, "PWD", new_pwd);
	update_export(ms->xprt, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
}

/**
 * Check and handle errors in the cd command.
 *
 * @param ms         A pointer to the t_minishell struct.
 * @param cmd_query  The command query string array.
 */
static void	check_errors(t_minishell *ms, char **cmd_query)
{
	struct stat		statbuf;

	if (cmd_query[1][0] == '~')
		cmd_query[1] = get_home(ms, cmd_query[1]);
	else if (ft_strlen(cmd_query[1]) == 1 && !ft_strncmp(cmd_query[1], "-", 1))
		cmd_query[1] = ft_strdup(get_env_info(&ms->env, "OLDPWD"));
	if (stat(cmd_query[1], &statbuf) == 0)
	{
		free_child(ms, cmd_query, 0);
		exit(0);
	}
	else if (cmd_query[1][0] == '-' && cmd_query[1][1])
		handle_error_cd(ms, cmd_query);
	else
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(cmd_query[1], STDERR_FILENO);
		ft_putstr_fd(": Invalid option\n", STDERR_FILENO);
		free_child(ms, cmd_query, 0);
		exit (1);
	}
}

/**
 * Check the cd command and perform the appropriate actions.
 * This function is executed only when running a single command,
 * in this case, 'cd'.
 *
 * @param ms         A pointer to the t_minishell struct.
 * @param cmd_query  The command query string array.
 */
void	check_cd(t_minishell *ms, char **cmd_query)
{
	int		status;
	int		i;

	i = 0;
	while (cmd_query[i])
		i++;
	wait(&status);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	if (g_exit == 0)
	{
		if (i == 1)
			execute_cd(ms, get_env_info(&ms->env, "HOME"));
		else
			execute_cd(ms, cmd_query[1]);
	}
}

/**
 * Validate command query and execute appropriate actions.
 *
 * @param ms         A pointer to the t_minishell struct.
 * @param cmd_query  The command query string array.
 */
void	cd(t_minishell *ms, char **cmd_query)
{
	int	i;

	i = 0;
	while (cmd_query[i])
		i++;
	if (i == 1)
	{
		free_child(ms, cmd_query, 0);
		g_exit = 0;
		exit (g_exit);
	}
	if (i > 2)
	{
		ft_putstr_fd("minishell: too many arguments\n", STDERR_FILENO);
		free_child(ms, cmd_query, 0);
		g_exit = 1;
		exit (g_exit);
	}
	else
		check_errors(ms, cmd_query);
}
