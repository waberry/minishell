#include "minishell.h"

void	exit_shell(t_vars *vars)
{
	free_tbl(vars->g_envv);
	free(vars);
	write(1, "\n", 1);
	exit(0);
}