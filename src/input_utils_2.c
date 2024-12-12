/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:44:00 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/12 22:28:22 by tsodre-p         ###   ########.fr       */
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