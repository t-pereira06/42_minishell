/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:10:19 by davioliv          #+#    #+#             */
/*   Updated: 2024/11/05 12:23:48 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(void)
{
	if (ft_strlen(ms()->input) > 5)
	{
		printf("no options allowed");
		return (0);
	}
	return (free_all(), ft_putstr("exit\n"), 0);
}
