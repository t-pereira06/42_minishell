/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:47:25 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/30 17:38:56 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Sets up custom signal handlers for heredoc operations.
 */
void	sigint_heredoc(void)
{
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * Signal handler function for handling the SIGINT signal.
 *
 * @param signal The signal number.
 */
void	handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
}

/**
 * Signal handler function for handling the SIGINT signal during the
 * child process execution.
 *
 * @param sig The signal number.
 */
void	handler_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

/**
 * Sets up custom signal handlers for the minishell program.
 */
void	signal_handling(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * Restores the default signal handling behavior for
 * SIGQUIT and SIGINT signals.
 */
void	signal_default(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
