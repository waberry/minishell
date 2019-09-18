#include "minishell.h"

/*
void	update_pwd(t_vars *vars)
{
	int		i;
	char	*tmp;

	i = get_var_index(vars, "PWD");
	tmp = get_var(vars, "PWD");
	if (ft_strcmp(vars->cwd, tmp) != 0)
	{
		free(vars->g_envv[i]);
		vars->g_envv[i] = ft_strdup("PWD=");
		vars->g_envv[i] = ft_strjoin(vars->g_envv[i], vars->cwd);
	}
}

void	cd_builtin(t_vars *vars, char *path)
{

}

void	parse_cd(t_vars *vars, char **command)
{

}
*/