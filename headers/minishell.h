/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:21:13 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/24 19:24:16 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <limits.h>

# define REDIRECT "><"
# define NOHANDLE "&;(){}*\\"

# define UNTOKEN "minishell: syntax error near unexpected token '"
# define NOSUPPORT "minishell: no support for operator '"

extern int	g_exit;

typedef struct s_minishell
{
	t_list	*env;
	t_list	*xprt;
	int		n_cmd;
	int		n_pipe;
	int		in_fd;
	int		out_fd;
	int		counter;
	int		*pipe_fd;
	pid_t	*pid;
	bool	heredoc;
	char	*prompt;
	char	*input;
	/* redirect use only */
	char	*operator;
	char	*temp;
	/* -------------- */
	char	**query;
	char	**args;
	char	**paths;
}				t_minishell;

typedef struct s_env
{
	char	*name;
	char	*info;
}				t_env;

typedef struct s_expander
{
	int		index;
	int		len;
	int		offset;
	int		quote;
	t_list	*temp;
}				t_expander;

//SRC

//check_builtins.c
int		do_builtin(t_minishell *ms, char **query);

//exec_redirects.c
void	change_fds(t_minishell *ms);
int		do_input(t_minishell *ms, char **query);
int		do_output(t_minishell *ms, char **query);
//int		do_heredoc(t_minishell *ms, char **query);
int		do_append(t_minishell *ms, char **query);

//exec_utils.c
void	get_exit_status(t_minishell *ms);
void	free_program(t_minishell *ms, int i);
char	*get_command(char *cmd, t_minishell *ms, int i);
void	free_child(t_minishell *ms, char **cmd_query, int i);

//exec.c
void	exec_command(t_minishell *ms, char **query);
void	exec_single_cmd(t_minishell *ms, char *cmd);
void	execute(t_minishell *ms);

//free.c
void	ft_free_lst(t_list *lst);

//get_env.c
t_list	*init_env(char **env);
t_env	*ft_create_data(char *info);
char	*get_name(char *info);
char	**ft_envcpy(t_list *env);

//input_errors.c
int		check_invalid_syntax(char *input);
//int		check_supported_op(char *input);
int		check_supported_op(t_minishell *ms, char *input, int i, int return_val);
int		check_quotes(char *input);
int		check_valid_input(t_minishell *ms, char *input);

//input_handling.c
int		read_input(t_minishell *ms);

//input_utils_2.c
int		print_syntax_err(char *error, char *str);
int		print_op_err(char *error, char *str);
int		error_token(char *error, char metachar, int dup);

//input_utils.c
char	get_quote(char c, char quote);
int		unexpected_tokens(char *input);
int		unexpected_redirect(char *input, int *i);

//parsing.c
char	*get_command(char *cmd, t_minishell *ms, int i);
void	parse_query(t_minishell *ms, char **cmd_query);

//prompt.c
char	*get_prompt(t_minishell *ms, int i, int j);

//redirects.c
int		query_count(char **query);
char	**erase_redir(char **query, int pos, int size, int j);
char	**check_redir(t_minishell *ms, char *input, int i, int err);

//signals.c
void	handler(int signal);
void	handler_sigint(int sig);
void	signal_handling(void);
void	signal_default(void);

//splitter.c
int		ft_wordcounter(char *str, char c);
int		ft_wordlen(char *str, char c);
char	**splitter(char *s, char c);

//utils.c
char	*get_env_info(t_list **env, char *name);
char	*add_whitespaces(char *str);
size_t	ft_cmdlen(char *str);
int		check_strcmp(char *s1, char *s2);
char	*ft_strcjoin(char const *s1, char c);

//BUILT-INS
void	ft_echo(t_minishell *ms, char **query);
void	ft_env(t_minishell *ms, char**query);
void	ft_cd(t_minishell *ms, char **query);

#endif
