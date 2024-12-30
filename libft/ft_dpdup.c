/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dpdup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:29:14 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/28 18:48:04 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	**ft_dpdup(char **dp, int size)
{
	int		i;
	char	**temp;

	i = -1;
	temp = (char **)malloc(sizeof(char *) * size);
	while (++i < size)
		if (dp[i])
			temp[i] = ft_strdup(dp[i]);
		else
			temp[i] = NULL;
	return (temp);
}
