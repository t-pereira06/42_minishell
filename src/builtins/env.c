/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davioliv <davioliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:04:00 by davioliv          #+#    #+#             */
/*   Updated: 2024/10/03 17:06:05 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_minishell *ms)
{
	t_list	*temp;

	if (ft_strlen(ms->input) > 4)
	{
		printf("no options allowed");
		return (0);
	}
	temp = ms->env;
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}
