/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:04:20 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/12 23:46:56 by tsodre-p         ###   ########.fr       */
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
			//((t_env *)(temp->content))->info = format_exp_variable(updt_info);
			((t_env *)(temp->content))->info = ft_strdup(updt_info);
			return ;
		}
		temp = temp->next;
	}
	//ft_lstadd_back(&lst, ft_lstnew(ft_create_export(updt_info)));
	ft_lstadd_back(&exp, ft_lstnew(ft_create_data(updt_info)));
}

/* void	add_to_list(void)
{
	int	i;

	i = 0;
	ft_lstadd_back(&ms()->export, ft_lstnew(ft_create_data(ms()->query[1])));
	while (ms()->query[1][i++])
	{
		if (ms()->query[1][i] == '=' && ms()->query[1][i + 1])
			ft_lstadd_back(&ms()->env,
				ft_lstnew(ft_create_data(ms()->query[1])));
	}
} */

/* void	show_list(void)
{
	t_list	*temp;
	t_env	*vars;

	temp = ft_calloc(1, sizeof(t_list));
	temp = ms()->export;
	while (temp->next)
	{
		vars = ft_calloc(1, sizeof(t_env));
		vars = (t_env *)temp->content;
		printf("declare -x ");
		printf("%s", vars->name);
		if (vars->info)
		{
			while (*vars->info != '=')
				vars->info++;
			vars->info++;
			printf("=");
			printf("\"");
			printf("%s", vars->info);
			printf("\"\n");
		}
		temp = temp->next;
		//free(vars);
	}
	ft_free_lst(temp);
} */

/**
 * Print the exported environment variables in ascii name order.
 *
 * @param lst The list of exported environment variables.
 */
void	show_list(void)
{
	int		i;
	char	**copy;

	i = 0;
	copy = ft_envcpy(ms()->export);
	while (i < ft_lstsize(ms()->export))
	{
		printf("declare -x ");
		printf("%s\n", copy[i++]);
	}
	ft_free_split(copy);
}


/**
 * Update the environment variables in the minishell structure.
 *
 * @param ms    The minishell structure.
 * @param info  The string containing the environment variable information.
 */
void	configure_variable(char *info)
{
	int		i;
	char	*name;

	i = 0;
	while (info[i] && info[i] != '=')
		i++;
	if (info[i] != '=')
	{
		name = ft_substr(info, 0, i);
		ft_update_exp(ms()->export, name, info);
		free(name);
		return ;
	}
	name = ft_substr(info, 0, i);
	ft_update_env(ms()->env, name, info);
	ft_update_exp(ms()->export, name, info);
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
	if (g_exit_status != 0)
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
