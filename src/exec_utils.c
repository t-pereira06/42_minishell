/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:31:30 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/21 13:40:35 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Retrieves the exit status of the child processes spawned by the minishell.
 *
 * @param ms A pointer to the minishell structure.
 */
void	get_exit_status(t_minishell *ms)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	status = 0;
	while (i < ms->n_cmd)
	{
		signal(SIGINT, &handler_sigint);
		pid = waitpid(ms->pid[i++], &status, 0);
		if (pid < 0)
			continue ;
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit = 128 + WTERMSIG(status);
	}
}

/**
 * Frees the memory allocated for the program.
 *
 * @param ms The minishell structure.
 * @param i  Flag indicating whether to free the environment list.
 */
void	free_program(t_minishell *ms, int i)
{
	free(ms->pid);
	if (ms->pipe_fd)
		free(ms->pipe_fd);
	unlink(".heredoc");
	if (ms->paths)
		ft_free_split(ms->paths);
	if (ms->args)
		ft_free_split(ms->args);
	if (i == 1)
		ft_free_lst(ms->env);
}

/**
 * Retrieves the full path of a command executable.
 *
 * @param cmd  The command name.
 * @param ms   Pointer to the minishell structure.
 * @param i    Index variable for string traversal.
 * @return     The full path of the command executable, or NULL if not found.
 */
char	*get_command(char *cmd, t_minishell *ms, int i)
{
	char	*temp;
	char	*command;

	if (!cmd)
		return (0);
	if (!get_env_info(&ms->env, "PATH"))
		return ("NO_PATH_AVAILABLE");
	if (!access(cmd, X_OK))
		return (cmd);
	while (ms->paths[i])
	{
		temp = ft_strdup(ms->paths[i]);
		command = ft_strjoin(temp, "/");
		free(temp);
		temp = ft_strdup(command);
		free(command);
		command = ft_strjoin(temp, cmd);
		if (!access(command, F_OK))
			return (command);
		free(temp);
		free(command);
		i++;
	}
	return (0);
}

/**
 * Frees the memory allocated for a child process in the program.
 *
 * @param ms         The minishell structure.
 * @param cmd_query  The command query array.
 * @param i          Flag indicating whether to exit the child process.
 */
void	free_child(t_minishell *ms, char **cmd_query, int i)
{
	if (cmd_query)
		ft_free_split(cmd_query);
	if (ms->pipe_fd)
		free(ms->pipe_fd);
	unlink(".heredoc");
	if (ms->paths)
		ft_free_split(ms->paths);
	if (ms->query)
		ft_free_split(ms->query);
	if (ms->args)
		ft_free_split(ms->args);
	ft_free_lst(ms->env);
	if (ms->pid)
		free(ms->pid);
	//ft_free_lst(ms->xprt);
	if (i == 1)
	{
		g_exit = 1;
		exit (1);
	}
}
