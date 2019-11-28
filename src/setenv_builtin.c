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

	if (!(ret = (char **)malloc(sizeof(char *) * (get_tbl_len(env) + 1))))
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

t_vars	*init_vars(char **env)
{
	t_vars	*ret;

	if (!(ret = (t_vars *)malloc(sizeof(t_vars))))
		return (NULL);
	ret->g_envv = load_env_var(env);
	ret->hist = NULL;
	ret->user_input = NULL;
	ret->commands = NULL;
	return (ret);
}

void	add_var(t_vars *vars, char *varname, char *value)
{
	int		init_size;
	int		i;
	char	**new_env;
	char	*tmp;

	init_size = get_tbl_len(vars->g_envv);
	if (!(new_env = (char **)malloc(sizeof(char *) * (init_size + 2))))
		return ;
	i = 0;
	while (vars->g_envv[i])
	{
		new_env[i] = ft_strdup(vars->g_envv[i]);
		++i;
	}
	new_env[i] = ft_strjoin(varname, "=");
	tmp = new_env[i];
	new_env[i] = ft_strjoin(new_env[i], value);
	free(tmp);
	new_env[++i] = NULL;
	free_tbl(vars->g_envv);
	vars->g_envv = new_env;
}

void	change_value(t_vars *vars, char **command)
{
	char	tmp[PATH_MAX];
	int		i;

	ft_bzero(tmp, PATH_MAX);
	ft_strcat(tmp, command[1]);
	ft_strcat(tmp, "=");
	if (!command[2])
		ft_strcat(tmp, "@");
	else
		ft_strcat(tmp, command[2]);
	i = get_var_index(vars, command[1]);
	free(vars->g_envv[i]);
	vars->g_envv[i] = ft_strdup(tmp);
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
	if (!command[2])
		return ;
	if (command[1][0] == '$')
		return ;
	if (command[2] && command[2][0] == '\"')
		remove_quotes(&command[2]);
	if (get_var_index(vars, command[1]) == -1)
		add_var(vars, command[1], command[2]);
	else
		change_value(vars, command);
}
