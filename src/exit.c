/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:27:52 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/09/29 20:28:02 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_lst(t_list *l)
{
	t_list	*p;

	if (!l)
		return ;
	p = l;
	while (l)
	{
		l = l->next;
		free(p->content);
		free(p);
		p = l;
	}
	l = NULL;
}


void		exit_shell(t_vars *vars)
{
	t_list	*ptr;

	ptr = vars->hist;
	free_lst(vars->hist);
	free_tbl(vars->g_envv);
	if (vars->user_input)
		free(vars->user_input);
	free(vars);
	exit(0);
}
