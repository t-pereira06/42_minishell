/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:06:10 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/16 15:00:58 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Handles error checking for the `cd` command.
 *
 * - Checks for invalid options and print the error.
 *
 * - Verifies if the "OLDPWD" environment variable is set when
 *   using the`-` option.
 *
 * - Checks if the directory specified by `ms()->query[1]` exists.
 *
 * - Returns 0 if there are no errors, or 1 if an error is encountered,
 *   printing an appropriate error message.
 *
 * @return 0 if the path is valid and no errors were found, otherwise 1.
 */
int	cd_error_handler(void)
{
	struct stat	statbuf;

	if (!ft_strcmp(ms()->query[1], "--") || !ft_strcmp(ms()->query[1], "~"))
		return (0);
	if (ms()->query[1][0] == '-' && ft_strlen(ms()->query[1]) != 1)
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
	else if (stat(ms()->query[1], &statbuf) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(ms()->query[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

/**
 * Updates the specified environment variable (`env_var`) in `ms()->env`
 * with the current working directory.
 * Constructs a string in the format "env_var=cwd", updates the environment list,
 * and frees the allocated memory for the working directoryand the constructed
 * string.
 *
 * @param env_var The name of the environment variable to update.
 */
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

/**
 * Changes the current working directory based on the given argument.
 *
 * - If the argument is "-" (dash), it changes to the directory stored in the
 *   "OLDPWD" environment variable and updates the query with the new "OLDPWD".
 * - If the argument is "~" or "--", it changes to the "HOME" directory.
 * - Updates the "OLDPWD" and "PWD" environment variables accordingly
 *   after changing the directory.
 *
 * @param arg The argument provided with the `cd` command
 * (e.g., "-" for previous directory, "~" for home directory).
 */
void	ft_cd(char *arg, char **query)
{
	if (arg && !ft_strcmp(arg, "-"))
	{
		ft_putstr_fd(get_env_info(&ms()->env, "OLDPWD"), STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(query[1]);
		query[1] = ft_strdup(get_env_info(&ms()->env, "OLDPWD"));
	}
	else if (arg && (!ft_strcmp(arg, "~") || !ft_strcmp(arg, "--")))
	{
		free(query[1]);
		query[1] = ft_strdup(get_env_info(&ms()->env, "HOME"));
	}
	change_env_exp_var("OLDPWD");
	if (!arg)
		chdir(get_env_info(&ms()->env, "HOME"));
	else
		chdir(ms()->query[1]);
	change_env_exp_var("PWD");
}

/**
 * Handles the behavior of the `cd` command in a child process.
 *
 * - If only one argument is provided, the function simply frees resources and exits.
 * - If more than two arguments are provided, it outputs an error message
 *   "too many arguments".
 * - For valid argument scenarios, it handles potential errors using
 *   the `cd_error_handler`.
 * After processing, it frees resources and exits with the appropriate exit status.
 */
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

/**
 * Executes the `cd` command in the shell.
 *
 * Waits for the child process to complete, updates the global exit status,
 * and if successful, changes the directory based on the number of arguments.
 * - If no additional arguments are provided (`count == 1`), the function
 * 	 attempts to change to the home directory.
 * - If one additional argument is provided (`count == 2`), the function
 *   attempts to change to the specified directory.
 */
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
			ft_cd(NULL, ms()->query);
		else if (count == 2)
			ft_cd(ms()->query[1], ms()->query);
	}
}
