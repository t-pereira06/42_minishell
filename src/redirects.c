/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:53:38 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 17:37:52 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Counts the number of elements in a query (array of strings).
 *
 * This function iterates over the provided query array, counting how many
 * elements it contains.
 *
 * The count is returned as an integer value.
 *
 * @param query The array of strings (command arguments).
 * @return The number of elements in the query array.
 */
int	query_count(char **query)
{
	int	i;

	i = 0;
	while (query[i])
		i++;
	return (i);
}

/**
 * Erases redirection elements from the query array.
 *
 * This function creates a new array by copying the elements of the
 * original query array while skipping the specified redirection elements
 * (at `pos` and `pos + 1`).
 *
 * The original query array is freed, and the new array is returned.
 *
 * @param query The array of strings (command arguments).
 * @param pos The index of the element to be erased (redirection operator).
 * @param size The total number of elements in the query array
 * (used for allocation).
 * @param j The current index during iteration.
 * @return A new query array with the redirection elements removed.
 */
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
 * Checks for and handles redirections in the input command.
 *
 * This function splits the input into tokens and checks for
 * redirection symbols (`<`, `>`, `<<`, `>>`).
 *
 * It calls the appropriate redirection handling functions and performs
 * actions like input, output, heredoc, or append redirections based on the
 * symbols encountered.
 *
 * If no errors are found, the redirection symbols are erased from the query,
 * and file descriptors are updated accordingly.
 *
 * @param input The input command containing redirection symbols.
 * @param i The current index in the input string.
 * @param err The error status flag for redirection handling.
 * @return The updated query with redirections handled.
 */
char	**check_redir(char *input, int i, int err)
{
	ms()->temp_query = splitter(input, ' ');
	free(input);
	check_expand_quotes(ms()->temp_query);
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
