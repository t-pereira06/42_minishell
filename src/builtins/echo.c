/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:04:51 by davioliv          #+#    #+#             */
/*   Updated: 2024/12/19 16:19:40 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* void	ft_echo(char **query)
{
	int	i;
	int	j;

	i = 1;
	if (!(ft_strncmp(query[1], "-n", 2)))
		i++;
	while (query[i])
	{
		j = 0;
		while (query[i][j] && query[i][j] != '\n')
			printf("%c", query[i][j++]);
		if (query[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(query[1], "-n", 2))
		printf("\n");
} */

int	check_echo_option(void)
{
	if (!ms()->query[1])
		return (ft_putstr_fd("\n", STDOUT_FILENO), 0);
	else if (match_strings(ms()->query[1], "-n") && !ms()->query[2])
		return 0;
	else if (match_strings(ms()->query[1], "-n"))
		return (ms()->echo_option = true, 1);
	return 1;
}

void	print_echo(int start_pos)
{
	int	i;

	i = start_pos;
	while (ms()->query[i])
	{
		if (match_strings(ms()->query[i], "$?"))
			ft_putnbr_fd(g_exit_status, STDOUT_FILENO);
		else
			ft_putstr_fd(ms()->query[i], STDOUT_FILENO);
		if (ms()->query[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!ms()->echo_option)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	exec_echo_child(void)
{
	if (check_echo_option())
	{
		if (!ms()->echo_option)
			print_echo(1);
		else
			print_echo(2);
	}
	g_exit_status = 0;
	free_child(NULL, 0);
	exit (0);
}