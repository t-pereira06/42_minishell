/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:21:58 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/15 23:57:05 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Prepares and returns a sorted linked list of environment variables for export.
 *
 * This function first sorts the given environment variable array alphabetically 
 * using the `check_alpha` function. Then, it initializes a linked list 
 * representation of the environment variables using the `init_env` function.
 *
 * @param env The array of environment variables to process.
 * @return A linked list of sorted environment variables.
 */
t_list	*get_export(char **env)
{
	t_list	*temp;

	env = check_alpha(env);
	temp = init_env(env);
	return (temp);
}

/**
 * Sorts an array of strings alphabetically.
 *
 * This function iterates through the given array of environment variables
 * and sorts them in ascending lexicographical order. It uses the 
 * ft_strncmp function to compare strings and the ft_swap function 
 * to swap the positions of two strings when necessary.
 *
 * @param env The array of strings (environment variables) to sort.
 * @return The sorted array of strings.
 */
char	**check_alpha(char **env)
{
	int	i;
	int	j;
	int	list_len;

	i = 0;
	j = 0;
	list_len = 0;
	while (env[i++])
		list_len++;
	i = 0;
	while (i++ < list_len - 1)
	{
		j = 0;
		while (j++ < list_len - i - 1 && env[j + 1])
		{
			if (ft_strncmp(env[j], env[j + 1],
					check_bigger(env[j], env[j + 1])) > 0)
				ft_swap(&env[j], &env[j + 1]);
		}
	}
	return (env);
}


/**
 * Determines the length of the longer of two strings.
 *
 * Compares the lengths of the two given strings and returns the length
 * of the longer string. If both strings are of equal length, the length
 * of the first string is returned.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @return The length of the longer string, or the length of s1 if they are equal.
 */
int	check_bigger(char *s1, char *s2)
{
	if (ft_strlen(s1) >= ft_strlen(s2))
		return (ft_strlen(s1));
	else
		return (ft_strlen(s2));
}
