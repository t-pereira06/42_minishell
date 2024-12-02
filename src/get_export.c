/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:21:58 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/02 20:22:01 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_list	*get_export(char **env)
{
	t_list	*temp;

	env = check_alpha(env);
	temp = init_env(env);
	return (temp);
}

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
			if (ft_strncmp(env[j], env[j + 1], check_bigger(env[j], env[j + 1])) > 0)
				ft_swap(&env[j], &env[j + 1]);
		}
	}
	return (env);
}

void	ft_swap(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

int	check_bigger(char *s1, char *s2)
{
	if (ft_strlen(s1) >= ft_strlen(s2))
		return (ft_strlen(s1));
	else
		return (ft_strlen(s2));
}