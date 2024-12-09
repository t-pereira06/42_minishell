/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:53:38 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/09 14:25:49 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	query_count(char **query)
{
	int	i;

	i = 0;
	while (query[i])
		i++;
	return (i);
}

char	**erase_redir(char **query, int pos, int size, int j)
{
	char	**temp;
	int		i;

	i = 0;
	size = query_count(query);
	temp = ft_calloc(size + 1, sizeof(char *));
	while (query[++j])
	{
		if (j == pos || j == (pos + 1))
			continue ;
		else
		{
			temp[i] = ft_strdup(query[j]);
			i++;
		}
	}
	i = -1;
	while (query[++i])
		free(query[i]);
	free(query);
	return (temp);
}

/**
 * Handles the input/output redirections in the command query by
 * calling the corresponding functions.
 *
 * @param input  The input string containing the command query.
 *
 * @return The updated command query array after handling the redirections.
 */
char	**check_redir(char *input, int i, int err)
{
	//char	**query;
	ms()->temp_query = splitter(input, ' ');
	free(input);
	while (ms()->temp_query[++i])
	{
		if (match_strings(ms()->temp_query[i], "<"))
			err = do_input(&ms()->temp_query[i + 1]);
		if (match_strings(ms()->temp_query[i], ">"))
			err = do_output(&ms()->temp_query[i + 1]);
		if (match_strings(ms()->temp_query[i], "<<"))
			err = do_heredoc(ms()->temp_query, &ms()->temp_query[i + 1]);
		if (match_strings(ms()->temp_query[i], ">>"))
			err = do_append(&ms()->temp_query[i + 1]);
		if (err == 0)
		{
			ms()->temp_query = erase_redir(ms()->temp_query, i, 0, -1);
			i--;
		}
		if (err == 1)
			free_child(ms()->temp_query, 1);
		err = -1;
	}
	change_fds();
	return (ms()->temp_query);
}
