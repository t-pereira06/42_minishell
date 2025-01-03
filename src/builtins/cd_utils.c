/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 09:25:30 by tsodre-p          #+#    #+#             */
/*   Updated: 2025/01/03 09:28:45 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	cd_error_helper(void)
{
	struct stat	statbuf;

	if (!ft_strcmp(ms()->query[1], "-"))
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
	if (!ft_strcmp(ms()->query[1], "--") || !ft_strcmp(ms()->query[1], "~"))
	{
		if (!get_env_info(&ms()->env, "HOME"))
			return (ft_putstr_fd("minishell: cd: HOME not set\n",
					STDERR_FILENO), 1);
	}
	else if (ms()->query[1][0] == '-' && ft_strlen(ms()->query[1]) != 1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(ms()->query[1], STDERR_FILENO);
		ft_putstr_fd(": Invalid option\n", STDERR_FILENO);
		return (1);
	}
	else
		return (cd_error_helper());
	return (0);
}
