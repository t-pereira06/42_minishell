/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 23:55:17 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/15 23:56:17 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Swaps the values of two string pointers.
 *
 * @param s1 A pointer to the first string pointer.
 * @param s2 A pointer to the second string pointer.
 */
void	ft_swap(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}