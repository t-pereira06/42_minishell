/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:47:55 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/11/05 12:16:52 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Frees the memory allocated for a linked list.
 *
 * @param lst  The linked list to free.
 */
void	ft_free_lst(t_list *lst)
{
	t_list	*temp;
	t_list	*next;

	temp = lst;
	while (temp)
	{
		next = temp->next;
		free(((t_env *)(temp->content))->name);
		free(((t_env *)(temp->content))->info);
		free(temp->content);
		free(temp);
		temp = next;
	}
}
