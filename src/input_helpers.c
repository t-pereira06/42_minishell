/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:39:06 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/11/05 12:19:28 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Frees the operator in the minishell structure if it has been set.
 *
 * @param ms Pointer to the minishell structure containing the operator
 * to be freed.
 * @param j An integer flag indicating if the operator has
 * been used (1 if true).
 *
 * Frees the memory allocated for `ms->operator` and sets it to `NULL` if
 * `j` is 1 and `ms->operator` is not empty. This prevents memory leaks by
 * ensuring that `ms->operator` is only freed when necessary.
 */
void	helper_free_op(int j)
{
	if (j == 1 && *ms()->operator != '\0')
	{
		free(ms()->operator);
		ms()->operator = NULL;
	}
}

void	helper_free_dp(char **dp)
{
	int	i;

	i = -1;
	while (dp[++i])
		free(dp[i]);
	free(dp);
}

int	helper_check_pipe(char **query, int a)
{
	if (check_strcmp(query[0], "|")
		|| (check_strcmp(query[0], "|") && (!query[a - 1] || !query[a + 1])))
		return (1);
	if (a != 0)
	{
		if (query[a][0] == '|'
			&& ft_strchr("<>", query[a - 1][ft_strlen(query[a - 1]) - 1]))
			return (1);
	}
	return (0);
}
