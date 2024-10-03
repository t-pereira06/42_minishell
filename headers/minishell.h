/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:21:13 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/10/03 10:53:18 by tsodre-p         ###   ########.fr       */
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

//free.c
void	ft_free_lst(t_list *lst);

//get_env.c
t_list	*init_env(char **env);
t_env	*ft_create_data(char *info);
char	*get_name(char *info);
char	**ft_envcpy(t_list *env);

//input_handling.c
int		check_quotes(char *input);
int		read_input(t_minishell *ms);

//prompt.c
char	*get_prompt(t_minishell *ms, int i, int j);

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
char	get_quote(char c, char quote);
char	*get_env_info(t_list **env, char *name);
char	*add_whitespaces(char *str);
size_t	ft_cmdlen(char *str);
int		check_strcmp(char *s1, char *s2);

//BUILT-INS

#endif
