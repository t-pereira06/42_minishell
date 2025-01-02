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
		if (match_strings(((t_env *)(temp->content))->name, name))
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
char	*format_input(char *arg, int i, int j)
{
	char	*temp;
	char	quote;

	quote = 0;
	temp = ft_calloc(get_spaced_length(arg) + 1, sizeof(char));
	while (arg[i])
	{
		quote = get_quote(arg[i], quote);
		if (!quote && (arg[i] == '>' || arg[i] == '<'))
		{
			temp[j++] = ' ';
			temp[j++] = arg[i];
			if (arg[i + 1] == arg[i])
				temp[j++] = arg[++i];
			temp[j++] = ' ';
		}
		else
			temp[j++] = arg[i];
		i++;
	}
	temp[j] = '\0';
	return (temp);
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
size_t	get_spaced_length(char *arg)
{
	size_t	cmd_len;
	int		i;

	cmd_len = 0;
	i = -1;
	if (!arg)
		return (0);
	while (arg[++i])
	{
		if (arg[i] == '>' || arg[i] == '<')
			cmd_len += 3;
		else
			cmd_len++;
	}
	return (cmd_len);
}

/**
 * Compares two strings and checks if they are equal.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 *
 * @return Returns 1 if the strings are equal, 0 otherwise.
 */
int	match_strings(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2)
		&& !ft_strncmp(s1, s2, ft_strlen(s1)))
		return (1);
	return (0);
}
