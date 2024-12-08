/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:04:20 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/08 18:53:11 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Format the environment variable declaration for export.
 *
 * @param str  The environment variable declaration.
 * @return     The formatted string for export.
 */
/* char	*format_exp_variable(char *str)
{
	int		i;
	char	*name;
	char	*info;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
	{
		name = ft_strjoin("declare -x ", str);
		info = ft_strjoin(name, "=\"\"");
		return (free(name), info);
	}
	name = ft_substr(str, 0, i);
	info = ft_strjoin(name, "=\"");
	free(name);
	name = ft_strjoin(info, str + i + 1);
	free(info);
	info = ft_strjoin(name, "\"");
	free(name);
	name = ft_strjoin("declare -x ", info);
	free(info);
	return (name);
} */

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
		if ((check_strcmp(var_upd, ((t_env *)(temp->content))->name)))
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

void	add_to_list(void)
{
	int	i;

	i = 0;
	ft_lstadd_back(&ms()->export, ft_lstnew(ft_create_data(ms()->query[1])));
	while (ms()->query[1][i++])
	{
		if (ms()->query[1][i] == '=' && ms()->query[1][i + 1])
			ft_lstadd_back(&ms()->env, ft_lstnew(ft_create_data(ms()->query[1])));
	}
}

void	show_list(void)
{
	t_list	*temp;
	t_env	*vars;

	temp = ms()->export;
	while (temp->next)
	{
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
	}
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
		/* else
			export_error(ms, cmd_query); */
	}
	exit_status = 0;
	free_child(NULL, 0);
	exit(exit_status);
}

void	exec_export(void)
{
	int		count;
	int		child_status;

	count = ft_dpcount(ms()->query);
	wait(&child_status);
	if (WIFEXITED(child_status))
		exit_status = WEXITSTATUS(child_status);
	if (exit_status != 2)
	{
		if (count > 1)
		{
			count = 0;
			exit_status = 0;
			/* while (cmd_query[++i])
				if (check_val(cmd_query[i]))
					update_env(ms, cmd_query[i]); */
		}
	}
}