#include "minishell.h"

char	**load_env_var(char **env)
{
	int		i;
	char	**ret;

	if (!(ret=(char**)malloc(sizeof(char*)*get_tbl_len(env) + 1)))
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

char	*get_home_path(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], "HOME="))
		{
			return (ft_strdup(ft_strchr(env[i], '=') + 1));
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
	ret->home = get_home_path(env);
	getcwd(ret->cwd, PATH_MAX + 1);
	ret->g_envv = load_env_var(env);
	ret->m_commands = NULL;
	ret->s_command = NULL;
	return (ret);
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

void	add_var(t_vars *vars, char *varname, char *value)
{
	int		init_size;
	int		new_size;
	int		i;
	char	**new_env;

	init_size = get_tbl_len(vars->g_envv);
	new_size = init_size + 1;
	if (!(new_env=(char**)malloc(sizeof(char*) * new_size + 1)))
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

void	parse_setenv(t_vars *vars, char **command)
{
	int		i;
	char	*tmp;

	if (!command || !(*command))
		return;
	else if (!command[1])
		print_myenv(vars);
	else if (command[1][0] != '$' || command[1][0] != '\"')
		return ;
	else if (!command[2])
	{
		if (get_var_index(vars, command[1]) == -1)
			add_var(vars, command[1], NULL);
	}	
	else
	{
		i = get_var_index(vars, command[1]);
		tmp = ft_strdup(command[1]);
		tmp = ft_strjoin(tmp,  "=");
		tmp = ft_strjoin(tmp, command[2]);
		free(vars->g_envv[i]);
		vars->g_envv[i] = ft_strdup(tmp);
		free(tmp);
	}
}















