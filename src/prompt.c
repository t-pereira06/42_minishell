/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:34:32 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/28 16:37:39 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Retrieves environment variables and assigns their values to the
 * provided pointers.
 *
 * @param user  Pointer to store the value of the "USER"
 * environment variable.
 * @param temp  Pointer to store the value of the "SESSION_MANAGER"
 * environment variable.
 */
static void	get_env(char **user, char **temp)
{
	*user = getenv("USER");
	*temp = getenv("SESSION_MANAGER");
}

/**
 * Generates the prompt string based on the provided parameters.
 *
 * @param check   Boolean value indicating whether to use the full current
 * working directory or shorten it.
 * @param cwd     Current working directory string.
 * @param prompt  Prompt string prefix.
 * @param length  Length of the shortened current working directory.
 * @return        The generated prompt string.
 */
static char	*gd_utils(bool check, char *cwd, char *prompt, int length)
{
	char	*temp;

	if (check == false)
	{
		temp = ft_strdup(cwd);
		free(cwd);
		cwd = ft_strjoin(temp, "$ ");
		free(temp);
		temp = ft_strjoin(prompt, cwd);
		free(cwd);
		return (temp);
	}
	else
	{
		temp = ft_strdup(cwd + length);
		free(cwd);
		cwd = ft_strjoin("~", temp);
		free(temp);
		temp = ft_strjoin(cwd, "$ ");
		free(cwd);
		cwd = ft_strjoin(prompt, temp);
		free(temp);
		return (cwd);
	}
}

char	*prompt_wout_home(char *cwd, char *prompt)
{
	char	*temp;
	
	temp = ft_strdup(cwd);
	free(cwd);
	cwd = ft_strjoin(temp, "$ ");
	free(temp);
	temp = ft_strjoin(prompt, cwd);
	free(cwd);
	return (temp);
}

/**
 * Retrieves the current directory and generates the prompt string
 * based on the directory and prompt prefix.
 *
 * @param prompt  Prompt string prefix.
 * @return        The generated prompt string.
 */
static char	*get_directory(char *prompt)
{
	char	*cwd;
	size_t	length;

	cwd = getcwd(0, 0);
	if (get_env_info(&ms()->env, "HOME") == NULL)
		return (prompt_wout_home(cwd, prompt));
	length = ft_strlen(get_env_info(&ms()->env, "HOME"));
	if (length > ft_strlen(cwd))
		cwd = gd_utils(false, cwd, prompt, length);
	else
		cwd = gd_utils(true, cwd, prompt, length);
	return (cwd);
}

/**
 * Generates the prompt string based on the user and current directory.
 *
 * @param i   Index variable for string traversal.
 * @param j   Index variable for string traversal.
 * @return    The generated prompt string.
 */
char	*get_prompt(int i, int j)
{
	char	*prompt;
	char	*user;
	char	*temp;

	get_env(&user, &temp);
	if (!user || !temp)
		return (NULL);
	prompt = ft_strdup(user);
	while (temp[i] != '/')
		i++;
	user = ft_strjoin(prompt, "@");
	free(prompt);
	while (temp[++i] != '.')
		j++;
	prompt = ft_substr(temp, i - j, j);
	temp = ft_strjoin(user, prompt);
	free(prompt);
	free(user);
	prompt = ft_strjoin(temp, ":");
	free(temp);
	temp = get_directory(prompt);
	free(prompt);
	return (temp);
}
