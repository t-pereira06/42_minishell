/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davioliv <davioliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:20:56 by davioliv          #+#    #+#             */
/*   Updated: 2024/10/03 17:03:46 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_minishell *ms)
{
	char	*temp;

	if (ft_strlen(ms->input) > 4)
	{
		printf("no options allowed");
		return (0);
	}
	temp = getcwd(0, 0);
	printf("%s\n", temp);
}
