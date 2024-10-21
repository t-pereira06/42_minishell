/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:52:03 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/21 15:52:24 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	print_syntax_err(char *error, char *operator)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putchar_fd(operator[0], STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (1);
}
