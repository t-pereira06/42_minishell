/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:09:55 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 17:32:22 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Returns a pointer to the static `t_minishell` structure.
 *
 * This function provides access to the global `t_minishell` structure,
 * which holds the state of the minishell.
 * It initializes the structure only once and returns a pointer
 * to it on subsequent calls.
 *
 * @return A pointer to the static `t_minishell` structure.
 */
t_minishell	*ms(void)
{
	static t_minishell	ms;

	return (&ms);
}
