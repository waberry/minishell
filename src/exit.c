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

void	exit_shell(t_vars *vars)
{
	free_tbl(vars->g_envv);
	if (vars->user_input)
		free(vars->user_input);
	free(vars);
	write(1, "\n", 1);
	exit(0);
}
