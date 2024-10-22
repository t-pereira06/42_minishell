/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:53:38 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/22 14:03:49 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Handles the input/output redirections in the command query by
 * calling the corresponding functions.
 *
 * @param ms     The minishell structure.
 * @param input  The input string containing the command query.
 *
 * @return The updated command query array after handling the redirections.
 */
char	**check_redir(t_minishell *ms, char *input)
{
	char	**query;
	int		i;
	//int		count;

	i = -1;
	ms->in_fd = STDIN_FILENO;
	ms->out_fd = STDOUT_FILENO;
	//count = ft_wordcounter(input, ' ');
	query = splitter(input, ' ');
	free(input);
	while (query[++i])
	{
		if (check_strcmp(query[i], "<"))
			do_input(ms, &query[i + 1]);
		/* if (check_strcmp(query[i], ">"))
			do_output(ms, query, i); */
		/* if (check_strcmp(query[i], "<<"))
			do_heredoc(ms, query); */
		/* if (check_strcmp(query[i], ">>"))
			do_append(ms, query, i); */
	}
	//change_fds(ms);
	return (query);
}
