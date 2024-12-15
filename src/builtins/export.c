/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:04:20 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/15 23:50:50 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Updates an existing environment variable in a linked list.
 *
 * @param lst       The linked list containing the environment variables.
 * @param name      The name of the environment variable to update.
 * @param new_info  The new information for the environment variable.
 * @return 0 if the variable was successfully updated, 1 if the variable was
 * not found in the list.
 */
void	ft_update_exp(t_list *exp, char *var_upd, char *updt_info)
{
	t_list	*temp;

	if (!exp)
		return ;
	temp = exp;
	while (temp)
	{
		if ((match_strings(var_upd, ((t_env *)(temp->content))->name)))
		{
			free(((t_env *)(temp->content))->info);
			((t_env *)(temp->content))->info = ft_strdup(updt_info);
			return ;
		}
		temp = temp->next;
	}
	ft_lstadd_back(&exp, ft_lstnew(ft_create_data(updt_info)));
}

/**
 * Print the exported environment variables in ascii name order.
 *
 * @param lst The list of exported environment variables.
 */
void	show_list(void)
{
	int		i;
	char	**copy;
	char	**formatted_str;

	i = -1;
	copy = ft_envcpy(ms()->export);
	while (++i < ft_lstsize(ms()->export))
	{
		formatted_str = ft_split(copy[i], '=');
		printf("declare -x ");
		printf("%s=", formatted_str[0]);
		printf("%c", '\"');
		printf("%s\"\n", formatted_str[1]);
		ft_free_split(formatted_str);
	}
	ft_free_split(copy);
}


/**
 * Update the environment variables in the minishell structure.
 *
 * @param ms    The minishell structure.
 * @param info  The string containing the environment variable information.
 */
void	configure_variable(char *content)
{
	int		i;
	char	*name;

	i = 0;
	while (content[i] && content[i] != '=')
		i++;
	if (content[i] != '=')
	{
		name = ft_substr(content, 0, i);
		ft_update_exp(ms()->export, name, content);
		free(name);
		return ;
	}
	name = ft_substr(content, 0, i);
	ft_update_env(ms()->env, name, content);
	ft_update_exp(ms()->export, name, content);
	free(name);
}

void	exec_export_child(void)
{
	if (ft_dpcount(ms()->query) == 1)
		show_list();
	else if (ft_dpcount(ms()->query) > 1)
	{
		if (ms()->query[1][0] == '-')
		{
			ft_putstr_fd("minishell: export: no options supported\n",
				STDERR_FILENO);
			free_child(NULL, 0);
			exit (2);
		}
		else
			g_exit_status = valid_syntax();
	}
	free_child(NULL, g_exit_status);
	exit(g_exit_status);
}

void	exec_export(void)
{
	int		count;
	int		child_status;

	count = ft_dpcount(ms()->query);
	wait(&child_status);
	if (WIFEXITED(child_status))
		g_exit_status = WEXITSTATUS(child_status);
	if (g_exit_status == 0)
	{
		if (count > 1)
		{
			count = 0;
			g_exit_status = 0;
			while (ms()->query[++count])
				configure_variable(ms()->query[count]);
		}
	}
}
