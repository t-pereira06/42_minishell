/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:35:14 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/30 11:36:20 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/**
 * Concatenate one string with a character into a newly allocated string.
 *
 * @param s1 - The first string.
 * @param c - The character.
 *
 * @return A pointer to the newly allocated concatenated string.
 *         If memory allocation fails or either input string is NULL,
 *         it returns NULL.
 */
char	*ft_strcjoin(char const *s1, char c)
{
	char			*join;
	unsigned int	i;
	unsigned int	j;
	unsigned int	size;

	i = 0;
	j = 0;
	if (!s1 || !c)
		return (0);
	size = ft_strlen(s1) + 1;
	join = (char *)malloc(sizeof(char) * (size + 1));
	if (!join)
		return (0);
	while (s1[j])
		join[i++] = s1[j++];
	join[i++] = c;
	join[i] = '\0';
	return (join);
}
