/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:28:23 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/15 12:38:21 by davioliv         ###   ########.fr       */
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

void	single_cmd(t_minishell *ms, char* cmd)
{
	char	**cmd_query;
	char	*command;

	ms->pid[0] = fork();
	if (!ms->pid[0])
	{
		cmd_query = handle_query(ms, cmd);
		signal_default();
		if (!cmd_query[0])
			free_child(ms, cmd_query, 1);
		command = get_command(cmd_query[0], ms, 0);
//		printf("%s\n", cmd_query[0]);
		if (!(ft_strncmp(cmd_query[0], "echo", 4)))
			ft_echo(cmd_query);
		else if (!(ft_strncmp(cmd_query[0], "env", 3)))
			ft_env(ms);
		else if (!(ft_strncmp(cmd_query[0], "cd", 2)))
			ft_cd(cmd_query[1]);
		else
			execve(command, cmd_query, ft_envcpy(ms->env));
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
	single_cmd(ms, cmd);
	free(cmd);
	get_exit_status(ms);
	free_program(ms, 0);
}
