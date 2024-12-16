/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:04:00 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/16 14:51:16 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Updates or adds an environment variable in the linked list.
 *
 * This function iterates through the linked list `env` to find the environment
 * variable specified by `var_upd`. If the variable exists, its associated
 * value (`info`) is updated with the new information provided in `updt_info`.
 * If the variable doesn't exist, a new environment variable is created and
 * added to the end of the list with the given information.
 *
 * @param env The linked list of environment variables to update.
 * @param var_upd The name of the environment variable to update.
 * @param updt_info The new value to assign to the specified
 * environment variable.
 */
void	ft_update_env(t_list *env, char *var_upd, char *updt_info)
{
	t_list	*temp;

	if (!env)
		return ;
	temp = env;
	while (temp)
	{
		if (match_strings(var_upd, ((t_env *)(temp->content))->name))
		{
			free(((t_env *)(temp->content))->info);
			((t_env *)(temp->content))->info = ft_strdup(updt_info);
			return ;
		}
		temp = temp->next;
	}
	ft_lstadd_back(&env, ft_lstnew(ft_create_data(updt_info)));
}

/**
 * Displays the environment variables.
 *
 * This function processes the environment variables linked list pointed to
 * by `ms()->env`, printing each variable's name and its associated value
 * (if present) to the standard output. It handles cases where the environment
 * variable info includes an '=' character.
 * If the function is called with an argument longer than 3 characters,
 * it prints an error message "no options allowed" and returns without
 * performing the environment listing.
 *
 * @param query The command arguments (should be NULL for this function).
 */
void	exec_env_child(void)
{
	int		i;
	char	**copy;

	i = -1;
	copy = ft_envcpy(ms()->env);
	if (ft_dpcount(ms()->query) != 1)
	{
		printf("minishell: env: no options allowed\n");
		ft_free_split(copy);
		g_exit_status = 1;
		free_child(NULL, 1);
		exit(g_exit_status);
	}
	while (++i < ft_lstsize(ms()->env))
		printf("%s\n", copy[i]);
	ft_free_split(copy);
	free_child(NULL, 0);
	g_exit_status = 0;
	exit (0);
}
