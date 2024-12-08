/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:04:00 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/08 17:00:46 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_env(t_list *env, char *var_upd, char *updt_info)
{
	t_list	*temp;

	if (!env)
		return ;
	temp = env;
	while (temp)
	{
		if (check_strcmp(var_upd, ((t_env *)(temp->content))->name))
		{
			free(((t_env *)(temp->content))->info);
			((t_env *)(temp->content))->info = ft_strdup(updt_info);
			return ;
		}
		temp = temp->next;
	}
	ft_lstadd_back(&env, ft_lstnew(ft_create_data(updt_info)));
}

void	ft_env(char **query)
{
	t_list	*temp;
	t_env	*vars;

	if (ft_strlen(ms()->args[0]) > 3)
	{
		printf("no options allowed");
		return ;
	}
	temp = ms()->env;
	while (temp->next)
	{
		vars = (t_env *)temp->content;
		printf("%s", vars->name);
		if (vars->info)
		{
			while (*vars->info != '=')
				vars->info++;
			printf("%s\n", vars->info);
		}
		temp = temp->next;
	}
	free_child(query, 0);
	exit_status = 0;
	exit (0);
}
