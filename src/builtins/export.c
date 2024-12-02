#include "../../headers/minishell.h"

void	add_to_list(char **query)
{
	int	i;

	i = 0;
	ft_lstadd_back(&ms()->xprt, ft_lstnew(ft_create_data(query[1])));
	while (query[1][i++])
	{
		if (query[1][i] == '=' && query[1][i + 1])
			ft_lstadd_back(&ms()->env, ft_lstnew(ft_create_data(query[1])));
	}
}

void	show_list(tvoid)
{
	t_list	*temp;
	t_env	*vars;

	temp = ms()->xprt;
	while (temp->next)
	{
		vars = (t_env *)temp->content;
		printf("declare -x ");
		printf("%s", vars->name);
		if (vars->info)
		{
			while (*vars->info != '=')
				vars->info++;
			vars->info++;
			printf("=");
			printf("\"");
			printf("%s", vars->info);
			printf("\"\n");
		}
		temp = temp->next;
	}
}

void	ft_export(t_minishell *ms, char **query)
{
	if (query[1])
		add_to_list(query);
	else
		show_list();
}