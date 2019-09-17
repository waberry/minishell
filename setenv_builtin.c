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

void	parse_setenv(t_vars *vars, char **command)
{
	int		i;
	char	*tmp;

	if (!command || !(*command))
		return;
	else if (!command[1] || !command[2])
		print_myenv(vars);
	else
	{
		i = get_var_index(vars, command[1]);
		if (i == -1)
			return ;
		tmp = ft_strdup(command[1]);
		tmp = ft_strjoin(tmp,  "=");
		tmp = ft_strjoin(tmp, command[2]);
		free(vars->g_envv[i]);
		vars->g_envv[i] = ft_strdup(tmp);
		free(tmp);
	}
}