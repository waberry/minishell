#include "minishell.h"

int		run_commands(char **command, t_vars *vars)
{
	if (ft_strcmp(command[0], "exit") ==  0)
		exit_shell(vars);
	else if (ft_strcmp(command[0], "echo") == 0)
		parse_echo(vars, command);
	else if (ft_strcmp(command[0], "env") == 0)
		print_myenv(vars);
	else if (ft_strcmp(command[0], "setenv") == 0)
		parse_setenv(vars, command);
	else if (ft_strcmp(command[0], "unsetenv") == 0)
		parse_unsetenv(vars, command);
	else if (ft_strcmp(command[0], "cd") == 0)
		parse_cd(vars, command);
	else
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(command[0]);
		return (-1) ;
	}
	return (0);
}