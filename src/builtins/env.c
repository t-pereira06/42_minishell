/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:04:00 by davioliv          #+#    #+#             */
/*   Updated: 2024/11/05 12:23:32 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_env(t_list **env, char *var_upd, char *content)
{
	t_env	*vars;
	t_list	*temp;

	temp = *env;
	while (temp->next)
	{
		vars = (t_env *)temp->content;
		if (!(ft_strcmp(vars->name, var_upd)))
		{
			ft_strlcpy(vars->info, content, ft_strlen(content) + 1);
			break ;
		}
		temp = temp->next;
	}
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
	g_exit = 0;
	exit (0);
}
