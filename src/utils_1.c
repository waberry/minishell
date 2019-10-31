/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:43:24 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/10/17 15:43:28 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_tbl_len(char **tbl)
{
	int		count;

	count = 0;
	while (tbl[count])
		++count;
	return (count);
}

int		not_empty(char *s)
{
	int		res;
	size_t	i;

	res = 0;
	i = 0;
	while (s && s[i])
	{
		if (s[i] != '\t' || s[i] != ' ' || s[i] != '\n')
			return (1);
		++i;
	}
	return (0);
}

void	get_varname(char *var, char *tmp)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return ;
		tmp[i] = var[i];
		++i;
	}
}

int		get_var_index(t_vars *vars, char *varname)
{
	int		i;
	char	tmp[1024];

	i = 0;
	while (vars->g_envv[i])
	{
		get_varname(vars->g_envv[i], tmp);
		if (ft_strcmp(tmp, varname) == 0)
			return (i);
		else
			ft_bzero(tmp, 1024);
		++i;
	}
	return (-1);
}
