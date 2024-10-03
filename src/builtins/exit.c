/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davioliv <davioliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:10:19 by davioliv          #+#    #+#             */
/*   Updated: 2024/10/03 17:12:21 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_minishell *ms)
{
	if (ft_strlen(ms->input) > 5)
	{
		printf("no options allowed");
		return (0);
	}
	return (free_all(ms), ft_putstr("exit\n"), 0);
}
