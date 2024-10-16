/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:53:38 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/16 11:57:32 by tsodre-p         ###   ########.fr       */
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
	char	**cmd_query;
	/* int		i;
	int		count; */

	//i = 0;
	ms->in_fd = STDIN_FILENO;
	ms->out_fd = STDOUT_FILENO;
	//count = ft_wordcounter(input, ' ');
	cmd_query = splitter(input, ' ');
	free(input);
	/* while (cmd_query[i])
	{
		if (!ft_strncmp(cmd_query[i], "<", ft_strlen(cmd_query[i])))
			handle_in(cmd_query, ms, &i, &count);
		else if (!ft_strncmp(cmd_query[i], ">", ft_strlen(cmd_query[i])))
			handle_out(cmd_query, ms, &i, &count);
		else if (!ft_strncmp(cmd_query[i], ">>", ft_strlen(cmd_query[i])))
			handle_append(cmd_query, ms, &i, &count);
		else if (!ft_strncmp(cmd_query[i], "<<", ft_strlen(cmd_query[i])))
			heredoc(cmd_query, ms, &i, &count);
		i++;
	} */
	return (cmd_query);
}
