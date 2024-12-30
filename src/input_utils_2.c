/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:44:00 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 17:42:49 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Checks if the character at the specified position is an asterisk
 * surrounded by non-space characters.
 *
 * This function verifies whether the asterisk (`*`) at a given position in
 * the input string is not preceded or followed by spaces.
 *
 * @param pos The position of the character in the string.
 * @return 1 if the asterisk is correctly placed; otherwise, 0.
 */
int	verify_asterisc(int pos)
{
	if (ft_chrcmp(ms()->input[pos], '*'))
		if ((size_t)(pos - 1) >= 0 || (size_t)pos + 1 <= ft_strlen(ms()->input))
			if (ft_chrcmp(ms()->input[pos - 1], ' ')
				&& ft_chrcmp(ms()->input[pos + 1], ' '))
				return (1);
	return (0);
}

/**
 * Prints errors related to redirection tokens in the command query.
 *
 * This function checks the query for invalid redirection operators like `|`,
 * `>>`, `<<`, and others, and prints corresponding error messages when found.
 *
 * @param query The array of command arguments.
 * @param i The index of the current element being checked.
 * @return 1 if an error is found; otherwise, 0.
 */
int	print_redir_errors(char **query, int i)
{
	if (match_strings(query[i], "|") && !query[i + 1])
		return (print_token_err(ERR_TOKEN, '|', 0));
	else if (match_strings(query[i], "||") && !query[i + 1])
		return (print_token_err(ERR_TOKEN, '|', 0));
	else if (match_strings(query[i], ">|"))
		return (print_op_err(ERR_OP, ">|"));
	else if (match_strings(query[i], "<|"))
		return (print_op_err(ERR_OP, "<|"));
	else if ((match_strings(query[i], ">>")
			|| match_strings(query[i], "<<")
			|| match_strings(query[i], ">")
			|| match_strings(query[i], "<")) && !query[i + 1])
		return (print_op_err(ERR_TOKEN, "newline"));
	return (0);
}
