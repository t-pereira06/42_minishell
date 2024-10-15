/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davioliv <davioliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:04:00 by davioliv          #+#    #+#             */
/*   Updated: 2024/10/15 12:48:45 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_minishell *ms)
{
	t_list	*temp;
	t_env	*vars;

	if (ft_strlen(ms->args[0]) > 3)
	{
		printf("no options allowed");
		return ;
	}
	temp = ms->env;
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
}
