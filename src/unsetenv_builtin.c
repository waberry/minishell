/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 21:35:32 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/09/29 21:35:47 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_envvar(t_vars *vars, int toremove)
{
	int		i;
	int		j;
	char	**new_env;
	int		len;

	len = get_tbl_len(vars->g_envv);
	if (!(new_env = (char **)malloc(sizeof(char *) * (len + 1))))
		return ;
	i = 0;
	j = 0;
	while (i < len - 1)
	{
		if (j == toremove)
			++j;
		new_env[i] = ft_strdup(vars->g_envv[j]);
		++i;
		++j;
	}
	new_env[i] = NULL;
	free_tbl(vars->g_envv);
	vars->g_envv = new_env;
}

void	parse_unsetenv(t_vars *vars, char **command)
{
	int		i;
	char	tmp[PATH_MAX];

	ft_bzero(tmp, PATH_MAX);
	if (!command || !(*command))
		return ;
	if (!command[1])
		return ;
	if (command[1][0] == '$' || command[1][0] == '\"')
		return ;
	i = get_var_index(vars, (command[1]));
	if (i != -1)
		remove_envvar(vars, i);
	else
		return ;
}
