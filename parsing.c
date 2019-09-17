#include "minishell.h"

void	parse_handler(char *input, t_vars *vars)
{
	if (ft_strchr(input, ';') != NULL)
		parse_multi_commands(input, vars);
	else
		parse_solo_command(input, vars);
}

void	parse_multi_commands(char *input, t_vars *vars)
{
	if (vars->m_commands != NULL)
	{
		free(vars->m_commands);
		vars->m_commands = NULL;
	}
	vars->m_commands = ft_strsplit(input, ';');
}

void	parse_solo_command(char *input, t_vars *vars)
{
	
}