/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:17:47 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/09 14:11:50 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * The use of a global variable like g_exit_status allows the exit status to be
 * accessed
 * and modified from different parts of the program, including signal handlers
 * or functions that handle command execution. It provides a way to communicate
 * the exit status between different components of the minishell program.
 */
int	g_exit_status = 0;

/**
 * Frees the memory allocated for the minishell structure.
 *
 * @param ms The minishell structure to free.
 */
void	free_all(void)
{
	if (ms()->env)
		ft_free_lst(ms()->env);
	if (ms()->export)
		ft_free_lst(ms()->export);
	if (ms()->input)
		free(ms()->input);
}

int	main(int ac, char **av, char **env)
{
	int	i;

	(void)av;
	if (ac > 1)
		printf("minishell: wrong number of arguments\n");
	else
	{
		ms()->env = init_env(env);
		ms()->export = get_export(env);
		while (1)
		{
			i = 0;
			signal_handling();
			i = read_input();
			if (!i)
				continue ;
			else if (i == -1)
				break ;
			execute();
		}
		return (free_all(), ft_putstr("exit\n"), 0);
	}
	return (0);
}
