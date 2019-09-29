/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:29:11 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/09/29 21:03:52 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**load_env_var(char **env)
{
	int		i;
	char	**ret;

	if (!(ret = (char **)malloc(sizeof(char *) * get_tbl_len(env) + 1)))
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		ret[i] = ft_strdup(env[i]);
		++i;
	}
	ret[i] = NULL;
	return (ret);
}

char	*get_home_path(char **env, char *dest)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], "HOME="))
		{
			return (ft_strcpy(dest, ft_strchr(env[i], '=') + 1));
		}
		++i;
	}
	return (NULL);
}

t_vars	*init_vars(char **env)
{
	t_vars	*ret;

	if (!(ret = (t_vars *)malloc(sizeof(t_vars))))
		return (NULL);
	ret->g_envv = load_env_var(env);
	return (ret);
}

void	add_var(t_vars *vars, char *varname, char *value)
{
	int		init_size;
	int		i;
	char	**new_env;

	init_size = get_tbl_len(vars->g_envv);
	if (!(new_env = (char **)malloc(sizeof(char *) * init_size + 2)))
		return ;
	i = 0;
	while (vars->g_envv[i])
	{
		new_env[i] = ft_strdup(vars->g_envv[i]);
		++i;
	}
	new_env[i] = ft_strdup(varname);
	if (!value)
		new_env[i] = ft_strjoin(new_env[i], "=@");
	else
	{
		ft_strjoin(new_env[i], "=");
		ft_strjoin(new_env[i], value);
	}
	new_env[++i] = NULL;
	free_tbl(vars->g_envv);
	vars->g_envv = new_env;
}

void	change_value(t_vars *vars, char **command)
{
	char	*tmp;

	tmp = ft_strdup(command[1]);
	tmp = ft_strjoin(tmp, "=");
	if (!command[2])
		tmp = ft_strjoin(tmp, "@");
	else
		tmp = ft_strjoin(tmp, command[2]);
	free(vars->g_envv[get_var_index(vars, command[1])]);
	vars->g_envv[get_var_index(vars, command[1])] = ft_strdup(tmp);
	free(tmp);
}

void	parse_setenv(t_vars *vars, char **command)
{
	if (!command || !(*command))
		return ;
	if (!command[1])
	{
		print_myenv(vars);
		return ;
	}
	if (command[1][0] == '$' || command[1][0] == '\"')
		return ;
	if (get_var_index(vars, command[1]) == -1)
	{
		if (!command[2])
			add_var(vars, command[1], NULL);
	}
	else
		change_value(vars, command);
}