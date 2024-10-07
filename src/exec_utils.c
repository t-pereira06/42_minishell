/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:31:30 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/07 15:05:16 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Removes redirection symbols from the input string and returns
 * the resulting command query.
 *
 * @param input The input string containing redirection symbols.
 *
 * @return Returns an array of strings representing the command query
 * without redirection symbols.
 */
char	**remove_redirects(char *input)
{
	char	**cmd_query;
	int		i;
	int		count;

	i = 0;
	count = ft_wordcounter(input, ' ');
	cmd_query = splitter(input, ' ');
	/* while (cmd_query[i])
	{
		if (!ft_strncmp(cmd_query[i], "<", ft_strlen(cmd_query[i])))
			shift_redirect(cmd_query, &i, &count);
		else if (!ft_strncmp(cmd_query[i], ">", ft_strlen(cmd_query[i])))
			shift_redirect(cmd_query, &i, &count);
		else if (!ft_strncmp(cmd_query[i], "<<", ft_strlen(cmd_query[i])))
			shift_redirect(cmd_query, &i, &count);
		else if (!ft_strncmp(cmd_query[i], ">>", ft_strlen(cmd_query[i])))
			shift_redirect(cmd_query, &i, &count);
		i++;
	}*/
	return (cmd_query);
}
