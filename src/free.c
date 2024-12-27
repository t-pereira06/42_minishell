/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:47:55 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/20 16:00:32 by tsodre-p         ###   ########.fr       */
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

void	free_child_heredoc(void)
{
	if (ms()->temp_query)
		ft_free_split(ms()->temp_query);
	if (ms()->pipe_fd)
		free(ms()->pipe_fd);
	unlink(".heredoc");
	if (ms()->paths)
		ft_free_split(ms()->paths);
	if (ms()->query)
		ft_free_split(ms()->query);
	if (ms()->args)
		ft_free_split(ms()->args);
	ft_free_lst(ms()->env);
	if (ms()->pid)
		free(ms()->pid);
	ft_free_lst(ms()->export);
	g_exit_status = 1;
	exit (1);
}
