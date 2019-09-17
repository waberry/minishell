#include "minishell.h"



static void	ft_putstr_newline(char *s, int no_newline)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '\n' && no_newline)
			ft_putchar(s[i]);
		else
			ft_putchar(s[i]);
		++i;
	}
}
#include <stdio.h>
void	echo_builtin(t_vars *vars, char *string, int no_newline)
{	
	if (string[0] == '\"' && string[1] == '$')
		remove_quotes(&(string));
	if (string[0] == '$' || ft_strchr(string, '$'))
	{
		int i = get_var_index(vars, (string + 1));
		ft_putstr_newline(vars->g_envv[i], no_newline);
	}
	else
		ft_putstr_newline(string, no_newline);
}

void	parse_echo(t_vars *vars, char **command)
{
	int		i;
	
	if (!command)
		return;
	i = (ft_strcmp(command[1], "-n") == 0) ? 2 : 1;
	while (command[i])
	{
		if (ft_strcmp(command[1], "-n") == 0)
			echo_builtin(vars, (char*)command[i], 1);
		else
			echo_builtin(vars, (char*)command[i], 0);
		if (command[i+1])
			ft_putchar(' ');
		++i;
	}
	if (ft_strcmp(command[1], "-n") != 0)
		ft_putchar('\n');

}