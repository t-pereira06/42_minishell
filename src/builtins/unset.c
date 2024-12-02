#include "../../headers/minishell.h"

void	ft_unset(char **query)
{
	t_list	*temp;
	t_env	*vars;

	temp = ms()->export;
	while (temp->next)
	{
		vars = (t_env *)temp->next->content;
		if (ft_strncmp(vars->name, query[1], ft_strlen(query[1])))
		{
			if (temp->next->next)
				temp->next = temp->next->next;
			else
				temp->next = NULL;
			free(vars->name);
			free(vars->info);
			free(vars);
			break ;
		}
		temp = temp->next;
	}
}