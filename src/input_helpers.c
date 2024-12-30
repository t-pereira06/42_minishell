/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:39:06 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 17:27:54 by tsodre-p         ###   ########.fr       */
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

/**
 * Frees the memory allocated for a double pointer (array of strings).
 *
 * This function takes a double pointer (e.g., an array of strings),
 * iterates through each string in the array, frees the memory for each string,
 * and then frees the array itself.
 * This function ensures that all memory used by the array and its
 * elements is properly freed.
 *
 * @param dp A double pointer (array of strings) that needs to be freed.
 */

void	helper_free_dp(char **dp)
{
	int	i;

	i = -1;
	while (dp[++i])
		free(dp[i]);
	free(dp);
}

/**
 * Checks for invalid pipe usage in the command query.
 *
 * This function ensures that a pipe (`|`) is not incorrectly placed
 * (e.g., at the start, end, or after redirection symbols).
 *
 * @param query The array of command arguments.
 * @param a The current index in the array.
 * @return 1 if invalid pipe usage is found, otherwise 0.
 */
int	helper_check_pipe(char **query, int a)
{
	if (match_strings(query[0], "|")
		|| (match_strings(query[0], "|") && (!query[a - 1] || !query[a + 1])))
		return (1);
	if (a != 0)
	{
		if (query[a][0] == '|'
			&& ft_strchr("<>", query[a - 1][ft_strlen(query[a - 1]) - 1]))
			return (1);
	}
	return (0);
}
