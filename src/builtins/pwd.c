/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:20:56 by davioliv          #+#    #+#             */
/*   Updated: 2024/11/05 12:24:05 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*temp;

	if (ft_strlen(ms()->input) > 4)
	{
		printf("no options allowed");
		return (0);
	}
	temp = getcwd(0, 0);
	printf("%s\n", temp);
}
