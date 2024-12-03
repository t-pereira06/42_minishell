/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dpcount.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 00:04:54 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/03 00:07:13 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Counts the number of elements in a null-terminated array of strings.
 *
 * @param dp A null-terminated array of strings (char pointers).
 * @return      The number of non-NULL strings in the array.
 */
int ft_dpcount(char **dp)
{
    int count;

    count = 0;
    while (dp[count])
		count++;
    return (count);
}