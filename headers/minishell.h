/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:21:13 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/11/20 23:45:31 by tsodre-p         ###   ########.fr       */
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

# define ERR_TOKEN "minishell: syntax error near unexpected token '"
# define ERR_OP "minishell: no support for operator '"
# define ERR_PIPE "minishell: pipe: error creating pipe\n"

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
	char	**temp_query;
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

//ms.c
t_minishell	*ms(void);

//check_builtins.c
int		do_builtin(char **query);

//exec_redirects.c
void	change_fds();
int		do_input(char **query);
int		do_output(char **query);
int		do_heredoc(char **query, char **next);
int		do_append(char **query);

//exec_utils.c
void	get_exit_status(void);
void	free_program(int i);
char	*get_command(char *cmd, int i);
void	no_command_err(char *command, char **query);
void	free_child(char **cmd_query, int i);

//exec.c
void	exec_command(char **query);
void	exec_command_pipe(char *command, int n_pid);
void	exec_pipes(void);
void	single_cmd(char *cmd);
void	execute(void);

//expand.c
void	check_expand_quotes(char **query);

//free.c
void	ft_free_lst(t_list *lst);
void	free_child_heredoc(void);

//get_env.c
t_list	*init_env(char **env);
t_env	*ft_create_data(char *info);
char	*get_name(char *info);
char	**ft_envcpy(t_list *env);

//heredoc.c
void	heredoc_sigint(int signum);
void	err_heredoc(char **query);
void	err_eof(char *str);
void	helper_heredoc(char **input, char *lim);

//input_errors.c
int		handle_op(char *input, int i, int return_val);
int		unexpected_tokens(char *input);
int		check_valid_input(char *input);

//input_handling.c
int		read_input(void);

//input_helpers.c
void	helper_free_op(int j);
void	helper_free_dp(char **dp);
int		helper_check_pipe(char **query, int a);

//input_prterr.c
int		print_syntax_err(char *error, char *str);
int		print_op_err(char *error, char *str);
int		print_token_err(char *error, char metachar, int dup);

//input_utils.c
int		check_op(char *operator, char *input, int a);
int		helper_operator(char *input, int a);
int		search_quote(char *query);
int		check_pipe(char *string, char**query, int a, int quote);
int		unexpected_redirect(char **query);

//parsing.c
char	*get_command(char *cmd, int i);
void	parse_query(char **cmd_query);

//pipes.c
void	close_pipes_fd(int i);
void	change_standard_io(int in_fd, int out_fd);
void	manage_pipeline_io(int n_pid);
void	do_pipex(void);

//prompt.c
char	*get_prompt(int i, int j);

//quotes.c
int		len_quoteless(char *arg);
void	find_quote(char *arg, int *i, char *quote);
char	*remove_quotes(char *arg);
int		check_quotes(char *input);
char	get_quote(char c, char quote);

//redirects.c
int		query_count(char **query);
char	**erase_redir(char **query, int pos, int size, int j);
char	**check_redir(char *input, int i, int err);

//signals.c
void	sigint_heredoc(void);
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

//BUILT-INS
void	ft_echo(char **query);
void	ft_env(char**query);
void	ft_cd(char **query);

#endif
