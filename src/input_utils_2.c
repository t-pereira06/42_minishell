/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:44:00 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/27 11:19:19 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	verify_asterisc(int pos)
{
	if (ft_chrcmp(ms()->input[pos], '*'))
		if ((size_t)(pos - 1) >= 0 || (size_t)pos + 1 <= ft_strlen(ms()->input))
			if (ft_chrcmp(ms()->input[pos - 1], ' ')
				&& ft_chrcmp(ms()->input[pos + 1], ' '))
				return (1);
	return (0);
}

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
