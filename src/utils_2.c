/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:44:01 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/11/21 18:55:56 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char **s)
{
	char	*tmp;
	int		i;

	if (!s || !(*s))
		return ;
	if (!(tmp = (char*)malloc(sizeof(char) * ft_strlen(*s))))
		return ;
	i = ft_strlen(*s) - 2;
	tmp = ft_strcpy(tmp, (*s + 1));
	while (i < (int)ft_strlen(tmp))
	{
		tmp[i] = '\0';
		++i;
	}
	free(*s);
	*s = ft_strdup(tmp);
	free(tmp);
}

void	free_tbl(char **tbl)
{
	int		i;

	if (!tbl || !*tbl)
		return ;
	i = 0;
	while (tbl[i])
	{
		free(tbl[i]);
		++i;
	}
	free(tbl);
	tbl = NULL;
}

int		ft_strchri_last(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == c)
			return (i);
		--i;
	}
	return (-1);
}

char	*get_var(t_vars *vars, char *varname)
{
	int		i;
	char	tmp[PATH_MAX];

	i = 0;
	ft_bzero(tmp, PATH_MAX);
	while (vars->g_envv[i])
	{
		get_varname(vars->g_envv[i], tmp);
		if (ft_strcmp(tmp, varname) == 0)
			return ((ft_strchr(vars->g_envv[i], '=') + 1));
		else
			ft_bzero(tmp, 1024);
		++i;
	}
	return (NULL);
}

void	print_myenv(t_vars *vars)
{
	int		i;
	char	*value;
	char	varname[1024];

	i = 0;
	while (i < get_tbl_len(vars->g_envv))
	{
		ft_bzero(varname, 1024);
		get_varname(vars->g_envv[i], varname);
		value = get_var(vars, varname);
		if (ft_strcmp(value, "@") != 0)
			ft_putendl(vars->g_envv[i]);
		++i;
	}
}
