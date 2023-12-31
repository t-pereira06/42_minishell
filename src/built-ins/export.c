/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:10:33 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 12:31:29 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Check if a string is a valid environment variable assignment.
 * The string should be in the format "name=value".
 *
 * @param str The string to check.
 * @return 1 if the string is a valid environment variable assignment,
 * 0 otherwise.
 */
int	check_val(char *str)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[size] && str[size] != '=')
		size++;
	while (i < size)
	{
		if (!ft_isalnum_extra(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * Handle export command errors.
 * Prints an error message for each invalid identifier in the
 * command arguments.
 *
 * @param ms The minishell structure.
 * @param cmd_query The command arguments.
 */
void	export_error(t_minishell *ms, char **cmd_query)
{
	int	i;

	i = 1;
	g_exit = 0;
	while (cmd_query[i])
	{
		if (!check_val(cmd_query[i]))
		{
			ft_putstr_fd("minishell: export: '", STDERR_FILENO);
			ft_putstr_fd(cmd_query[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			exit (1);
		}
		i++;
	}
	free_child(ms, cmd_query, 0);
	exit (0);
}

/**
 * Print the exported environment variables in ascii name order.
 *
 * @param lst The list of exported environment variables.
 */
void	exp_print(t_list *lst)
{
	int		i;
	char	*cpy_i;
	char	*cpy_j;
	char	**copy;

	i = 0;
	copy = ft_envcpy(lst);
	while (i < ft_lstsize(lst) - 1)
	{
		if (ft_strncmp(copy[i], copy[i + 1],
				ft_maxlen(copy[i], copy[i + 1])) > 0)
		{
			cpy_i = ft_strdup(copy[i]);
			cpy_j = ft_strdup(copy[i + 1]);
			free_cpy(copy[i], copy[i + 1]);
			copy[i] = ft_strdup(cpy_j);
			copy[i + 1] = ft_strdup(cpy_i);
			free_cpy(cpy_i, cpy_j);
			i = 0;
		}
		else
			i++;
	}
	print(ft_lstsize(lst), copy);
}

/**
 * Execute the export command and perform the necessary actions.
 *
 * @param ms         The minishell structure.
 * @param cmd_query  The command and arguments.
 */
void	do_export(t_minishell *ms, char **cmd_query)
{
	int	i;

	i = 0;
	while (cmd_query[i])
		i++;
	if (i == 1)
		exp_print(ms->xprt);
	else if (i > 1)
	{
		if (cmd_query[1][0] == '-')
		{
			ft_putstr_fd("minishell: export: no options supported\n",
				STDERR_FILENO);
			free_child(ms, cmd_query, 0);
			exit (2);
		}
		else
			export_error(ms, cmd_query);
	}
	free_child(ms, cmd_query, 0);
	g_exit = 0;
	exit(g_exit);
}
