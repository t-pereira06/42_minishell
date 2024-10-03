/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:17:47 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/03 14:26:17 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * The use of a global variable like g_exit allows the exit status to be
 * accessed
 * and modified from different parts of the program, including signal handlers
 * or functions that handle command execution. It provides a way to communicate
 * the exit status between different components of the minishell program.
 */
int	g_exit = 0;

/**
 * Frees the memory allocated for the minishell structure.
 *
 * @param ms The minishell structure to free.
 */
void	free_all(t_minishell ms)
{
	if (ms.env)
		ft_free_lst(ms.env);
	if (ms.xprt)
		ft_free_lst(ms.xprt);
	if (ms.input)
		free(ms.input);
}

int	main(int ac, char **av, char **env)
{
	int			i;
	t_minishell	ms;

	(void)av;
	if (ac > 1)
		printf("minishell: wrong number of arguments\n");
	else
	{
		ms.env = init_env(env);
		//ms.xprt = get_export(env);
		while (1)
		{
			i = 0;
			signal_handling();
			i = read_input(&ms);
			if (!i)
				continue;
			else if (i == -1)
				break;
			//execute(&ms);
		}
		return (free_all(ms), ft_putstr("exit\n"), 0);
	}
	return (0);
}
