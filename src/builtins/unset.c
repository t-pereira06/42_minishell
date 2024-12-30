/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:53:27 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 17:16:26 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Frees the memory allocated for an environment variable node.
 *
 * @param lst The list node containing the environment variable to free.
 */
void	free_node(t_list *lst)
{
	free(((t_env *)(lst->content))->name);
	free(((t_env *)(lst->content))->info);
	free((t_env *)lst->content);
}

/**
 * Removes a specified environment variable from the list.
 *
 * Searches for the variable `unset_var` in the list and removes it if found,
 * freeing the associated memory.
 *
 * @param lst The list from which to remove the variable.
 * @param unset_var The name of the environment variable to remove.
 */
void	do_unset(t_list *lst, char *unset_var)
{
	t_list	*temp;
	t_list	*prev;
	char	*temp_name;

	temp = lst;
	prev = 0;
	while (temp)
	{
		temp_name = ft_strdup(((t_env *)(temp->content))->name);
		if (match_strings(unset_var, temp_name))
		{
			if (prev)
				prev->next = temp->next;
			else
				lst = temp->next;
			free_node(temp);
			free(temp);
			free(temp_name);
			return ;
		}
		free(temp_name);
		prev = temp;
		temp = temp->next;
	}
}

/**
 * Executes the `unset` command in a child process.
 *
 * Checks for invalid options, handles the removal of environment variables,
 * and exits with the appropriate status.
 */
void	exec_unset_child(void)
{
	if (ft_dpcount(ms()->query) == 1)
	{
		g_exit_status = 0;
		free_child(NULL, 0);
		exit(g_exit_status);
	}
	else
	{
		if (ms()->query[1][0] == '-')
		{
			ft_putstr_fd("minishell: unset: no options supported\n",
				STDOUT_FILENO);
			g_exit_status = 2;
			free_child(NULL, 0);
			exit(g_exit_status);
		}
		g_exit_status = 0;
		free_child(NULL, 0);
		exit(g_exit_status);
	}
}

/**
 * Executes the `unset` command in the parent process.
 *
 * Waits for the child process, updates the exit status, and removes environment
 * variables from both the `env` and `export` lists if specified.
 */
void	exec_unset(void)
{
	int		count;
	int		i;
	int		child_status;

	i = 0;
	count = ft_dpcount(ms()->query);
	wait(&child_status);
	if (WIFEXITED(child_status))
		g_exit_status = WEXITSTATUS(child_status);
	if (g_exit_status == 0)
	{
		if (count > 1)
		{
			while (ms()->query[++i])
			{
				do_unset(ms()->export, ms()->query[i]);
				do_unset(ms()->env, ms()->query[i]);
			}
		}
	}
}
