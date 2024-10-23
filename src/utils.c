/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:40:49 by marvin            #+#    #+#             */
/*   Updated: 2023/05/29 10:40:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Retrieves the information associated with a given environment variable name.
 *
 * @param env  A pointer to the pointer of the linked list containing
 * environment variable data.
 * @param name The name of the environment variable to retrieve information for.
 *
 * @return Returns a pointer to the information associated with
 * the environment variable.
 * If the variable is not found, it returns NULL.
 */
char	*get_env_info(t_list **env, char *name)
{
	char	*info;
	t_list	*temp;

	temp = *env;
	while (temp)
	{
		if (check_strcmp(((t_env *)(temp->content))->name, name))
		{
			info = ft_strchr(((t_env *)(temp->content))->info, '=');
			info++;
			return (info);
		}
		temp = temp->next;
	}
	return (NULL);
}

/**
 * Adds whitespaces around redirection characters in a string.
 *
 * @param str The input string to modify.
 *
 * @return Returns a new string with whitespaces added around
 * redirection characters.
 */
char	*add_whitespaces(char *str)
{
	char	*res;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = 0;
	res = ft_calloc(ft_cmdlen(str) + 1, sizeof(char));
	while (str[i])
	{
		quote = get_quote(str[i], quote);
		if (!quote && ft_strchr("><", str[i]))
		{
			res[j++] = ' ';
			res[j++] = str[i++];
			if (str[i] == str[i - 1])
				res[j++] = str[i++];
			res[j++] = ' ';
		}
		res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

/**
 * Calculates the length of a null-terminated string until the first
 * whitespace character.
 *
 * @param str The null-terminated string to calculate the length of.
 *
 * @return Returns the length of the string until the first
 * whitespace character.
 */
size_t	ft_cmdlen(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_strchr("><", str[i]))
		{
			len += 3;
			i++;
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}

/**
 * Compares two strings and checks if they are equal.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 *
 * @return Returns 1 if the strings are equal, 0 otherwise.
 */
int	check_strcmp(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2)
		&& !ft_strncmp(s1, s2, ft_strlen(s1)))
		return (1);
	return (0);
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*join;
	unsigned int	i;
	unsigned int	j;
	unsigned int	size;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (size + 1));
	if (!join)
		return (0);
	while (s1[j])
		join[i++] = s1[j++];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	return (join);
}
