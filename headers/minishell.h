/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:21:13 by tsodre-p          #+#    #+#             */
/*   Updated: 2025/01/03 08:26:48 by tsodre-p         ###   ########.fr       */
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
# include <dirent.h>
# include <errno.h>

# define REDIRECT "><"
# define NOHANDLE "&;(){}*\\"

# define ERR_TOKEN "minishell: syntax error near unexpected token `"
# define ERR_OP "minishell: no support for operator '"
# define ERR_PIPE "minishell: pipe: error creating pipe\n"

extern int	g_exit_status;

typedef struct s_minishell
{
	t_list	*env;
	t_list	*export;
	/*  pipes use only   */
	int		n_cmd;
	int		n_pipe;
	int		in_fd;
	int		out_fd;
	int		*pipe_fd;
	/* ----------------- */
	pid_t	*pid;
	bool	heredoc;
	char	*prompt;
	char	*input;
	/* redirect use only */
	char	*operator;
	char	*temp;
	char	**temp_query;
	/* ----------------- */
	char	**query;
	char	**args;
	char	**exec_paths;
	/*   echo use only   */
	bool	echo_option;
	/* ----------------- */
}				t_minishell;

typedef struct s_env
{
	char	*name;
	char	*info;
}				t_env;

/* typedef struct s_expander
{
	int		index;
	int		len;
	int		offset;
	int		quote;
	t_list	*temp;
}				t_expander; */

/* ------------------- Source ------------------- */

//ms.c
t_minishell	*ms(void);

//check_builtins.c
int			do_builtin_child(void);
int			exec_parent_builtins(void);

//exec_redirects.c
void		change_fds(void);
int			handle_file_acess_errors(char *str);

//exec_redirects.c
int			do_input(char **query);
int			do_output(char **query);
int			do_heredoc(char **query, char **next);
int			do_append(char **query);

//exec_utils_2.c
void		check_dir(char *str);
int			check_if_dir_file(char *str);
void		no_path_err(char *command);

//exec_utils.c
void		get_exit_status(void);
void		free_program(int i);
char		*find_executable_path(char *cmd, int i);
void		no_cmd_err(char *command);
void		free_child(char **cmd_query, int i);

//exec.c
void		exec_command(char **query);
void		exec_command_pipe(char *command, int n_pid);
void		exec_pipes(void);
void		single_cmd(char *cmd);
void		execute(void);

//expand_args_utils.c
char		*get_var_wout_quote(char *str, int pos, char *final_expand);
char		*get_var_w_quote(char *str, int pos, char *final_expand);
char		*get_ohter_characters(char *str, int pos, char *final_expand);
void		remove_null_var(char **query, int count_before, int j);

//expand_args_2.c
int			var_len(char *str, char c);
char		*get_es_string(char *var_name);
char		*get_variable(char *str, int pos, int size);
char		*join_variable(char *before_var, char *var_str);
char		*trim_before_dsign(char *str);

//expand_args.c
char		*join_final_strings(char *final_str, char *final_expand);
char		*get_quote_string(char *str, int pos);
char		*check_variable(char *str, int pos, char *final_expand);
void		check_expand_quotes(char **query);

//free.c
void		ft_free_lst(t_list *lst);
void		free_child_heredoc(void);
void		free_all(void);

//get_env.c
t_list		*init_env(char **env);
t_env		*ft_create_data(char *info);
char		*get_name(char *info);
char		**ft_envcpy(t_list *env);

//get_export.c
t_list		*get_export(char **env);
char		**check_alpha(char **env);
void		ft_swap(char **s1, char **s2);
int			check_bigger(char *s1, char *s2);

//heredoc_utils.c
void		err_heredoc(char **query);
void		err_eof(char *str);
char		*expand_var_heredoc(char *buffer);

//heredoc.c
void		signals_heredoc(void);
void		heredoc_sigint(int signum);
void		helper_heredoc(char **query, char *delimiter,
				int file, char *buffer);

//input_errors.c
int			handle_op(char *input, int i, int return_val);
int			unexpected_tokens(char *input);
int			check_valid_input(char *input);

//input_handling.c
int			read_input(void);

//input_helpers.c
void		helper_free_op(int j);
void		helper_free_dp(char **dp);
int			helper_check_pipe(char **query, int a);

//input_prterr.c
int			print_syntax_err(char *error, char *str);
int			print_op_err(char *error, char *str);
int			print_token_err(char *error, char metachar, int dup);

//input_utils_2.c
int			verify_asterisc(int pos);
int			print_redir_errors(char **query, int i);

//input_utils.c
int			check_op(char *operator, char *input, int a);
int			helper_operator(char *input, int a);
int			search_quote(char *query);
int			check_pipe(char *string, char**query, int a, int quote);
int			unexpected_redirect(char **query);

//parsing.c
char		*find_executable_path(char *cmd, int i);
void		parse_query(char **cmd_query);

//pipes.c
void		close_pipes_fd(int i);
void		change_standard_io(int in_fd, int out_fd);
void		manage_pipeline_io(int n_pid);
void		do_pipex(void);

//prompt.c
void		get_env(char **user, char **temp);
char		*gd_utils(bool check, char *cwd, char *prompt, int length);
char		*prompt_wout_home(char *cwd, char *prompt);
char		*get_directory(char *prompt);
char		*get_prompt(int i, int j);

//quotes.c
int			len_quoteless(char *arg);
void		find_quote(char *arg, int *i, char *quote);
char		*trim_quotes(char *arg);
int			are_quotes_balanced(char *input);
char		get_quote(char c, char quote);

//redirects.c
int			query_count(char **query);
char		**erase_redir(char **query, int pos, int size, int j);
char		**check_redir(char *input, int i, int err);

//signals.c
void		sigint_heredoc(void);
void		handler(int signal);
void		handler_sigint(int sig);
void		signal_handling(void);
void		signal_default(void);

//splitter.c
int			ft_wordcounter(char *str, char c);
int			ft_wordlen(char *str, char c);
char		*get_word(char *str, char c, char **words);
char		**splitter(char *str, char c);

//utils.c
char		*get_env_info(t_list **env, char *name);
char		*format_input(char *arg, int i, int j);
size_t		get_spaced_length(char *arg);
int			match_strings(char *s1, char *s2);

/* ------------------- Built-ins ------------------- */

//cd.c
int			cd_error_handler(void);
void		change_env_exp_var(char *env_var);
void		ft_cd(char *arg, char **query);
void		exec_cd_child(void);
void		exec_cd(void);

//echo.c
int			check_echo_option(void);
void		print_echo(int start_pos);
void		exec_echo_child(void);

//env.c
void		ft_update_env(t_list *env, char *var_upd, char *updt_info);
void		exec_env_child(void);

//exit_utils.c
void		print_exit_error(void);
void		convert_number_exit(void);
void		numeric_error(char *str);
void		print_many_args(void);
void		print_non_numeric_arg(char *str);

//exit.c
void		exec_exit_child(void);
void		exec_exit(void);

//export_utils.c
int			ft_isalnum_extra(char c);
int			valid_syntax(void);

//export.c
void		ft_update_exp(t_list *exp, char *var_upd, char *updt_info);
void		show_list_export(void);
void		configure_variable(char *content);
void		exec_export_child(void);
void		exec_export(void);

//pwd.c
void		exec_pwd_child(void);

//unset.c
void		free_node(t_list *lst);
void		do_unset(t_list *lst, char *unset_var);
void		exec_unset_child(void);
void		exec_unset(void);

#endif
