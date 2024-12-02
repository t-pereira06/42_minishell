/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:20:36 by tsodre-p          #+#    #+#             */
/*   Updated: 2024/12/02 21:24:51 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
int builtins(void)
{
    ms()->query = splitter(ms()->args[0], ' ');
    if (!ms()->query[0])
		return ;
	expand_args(ms()->args, ms);
	if (check_strcmp("exit", ms()->query[0]))
		check_exit(ms, ms()->args);
	else if (check_strcmp("export", ms()->query[0]))
		check_export(ms, ms()->args);
	else if (check_strcmp("unset", ms()->query[0]))
		check_unset(ms, ms()->args);
	else if (check_strcmp("cd", ms()->query[0]))
		check_cd(ms, ms()->args);
    //still underwork
}