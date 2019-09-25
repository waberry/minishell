#include "minishell.h"



/*
	Dont forget to save old cwd when switching to new cwd
*/

static void	go_home(t_vars *vars)
{
	int		i;
	char	*home_path;

	i = get_var_index(vars, "OLDPWD")
	home_path = get_var(vars, "HOME")
	if (i = -1)
		add(vars, "OLDPWD", home_path);
	else
	{

	}
}

void	parse_cd(t_vars *vars, char **command)
{
	int		i;
	char	tmp[PATH_MAX + 1];

	if (!command || !*command)
		return ;
	if (!command[1])
		go_home(vars);
	if (command[1][0] == '\"')
		//remove quotes
	if (ft_strcmp(command[1],  "-") == 0)
		//go to last known pwd and stop
	if (command[1][0] == '$')
		//replace fill tmp with value or with command[2]
	i = 0;
	while (command[i])
	{
		ft_putstr(command[i]);
		ft_putchar(' ');
		++i;
	}
	ft_putchar('\n');
}