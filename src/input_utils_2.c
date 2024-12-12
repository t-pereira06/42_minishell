/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:44:00 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/12 17:44:23 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	verify_asterisc(int pos)
{
	if (ms()->input[pos] == '*')
		if (ms()->input[pos - 1] == ' ' 
			&& ms()->input[pos + 1] == ' ')
			return (1);
	return (0);
}