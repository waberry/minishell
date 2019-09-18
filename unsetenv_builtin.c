#include "minishell.h"

#include <stdio.h>
void	parse_unsetenv(t_vars *vars, char **command)
{
	int		i;

	if (!command || !(*command))
		return ;
	if (!command[1])
		return ;
	if (command[1][0] == '$' || command[1][0] == '\"')
		return ;
	i = get_var_index(vars, (command[1]));
	if (i == -1)
		return ;
	free(vars->g_envv[i]);
	vars->g_envv[i] = ft_strdup((command[1]));
	vars->g_envv[i] = ft_strjoin(vars->g_envv[i], "=");
	vars->g_envv[i] = ft_strjoin(vars->g_envv[i], "@");
}