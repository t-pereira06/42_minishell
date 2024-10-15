/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:28:23 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/15 15:50:16 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Handles the input/output redirections in the command query by
 * calling the corresponding functions.
 *
 * @param ms     The minishell structure.
 * @param input  The input string containing the command query.
 *
 * @return The updated command query array after handling the redirections.
 */
char	**handle_query(t_minishell *ms, char *input)
{
	char	**cmd_query;
/*	int		i;
	int		count;*/

//	i = 0;
	ms->in_fd = STDIN_FILENO;
	ms->out_fd = STDOUT_FILENO;
//	count = ft_wordcounter(input, ' ');
	cmd_query = splitter(input, ' ');
	free(input);
	return (cmd_query);
}

void	is_builtin(char	*command)
{
	if (!(ft_strncmp(ms->query[0], "echo", 4)))
		ft_echo(ms->query);
	else if (!(ft_strncmp(ms->query[0], "env", 3)))
		ft_env(ms);
	else if (!(ft_strncmp(ms->query[0], "cd", 2)))
		ft_cd(ms->query[1]);
	/*execute builtins inside child*/
}

void	do_builtin(t_minishell *ms)
{
	if (!(ft_strncmp(ms->query[0], "echo", 4)))
		ft_echo(ms->query);
	else if (!(ft_strncmp(ms->query[0], "env", 3)))
		ft_env(ms);
	else if (!(ft_strncmp(ms->query[0], "cd", 2)))
		ft_cd(ms->query[1]);
}

void	single_cmd(t_minishell *ms, char* cmd)
{
	char	**query;
	char	*command;

	ms->pid[0] = fork();
	if (!ms->pid[0])
	{
		signal_default();
		query = handle_query(ms, cmd);
		if (!query[0])
			free_child(ms, query, 1);
		command = get_command(query[0], ms, 0);
		is_builtin(query[0]);
//		printf("%s\n", query[0]);
		execve(command, query, ft_envcpy(ms->env));
		/*execute built-ins inside the child process*/
	}
}


/**
 * Function with instructions to execute single or multiple commands
 * in the minishell.
 *
 * @param ms The `t_minishell` structure containing relevant data.
 */
void	execute(t_minishell *ms)
{
	char	*cmd;

	cmd = add_whitespaces(ms->args[0]);
	//ms->query = handle_query(ms, cmd);
	single_cmd(ms, cmd);
	free(cmd);
	do_builtin(ms);
	//ft_free_split(ms->query);
	get_exit_status(ms);
	free_program(ms, 0);
}
