#include "minishell.h"

static void	save_pwd(t_vars *vars)
{
	int		i;
	char	*tmp;

	i = get_var_index(vars, "OLDPWD");
	if (i == -1)
		add_var(vars, "OLDPWD", get_var(vars, "PWD"));
	else
	{
		tmp = ft_strdup("OLDPWD");
		tmp = ft_strjoin(tmp,  "=");
		tmp = ft_strjoin(tmp, get_var(vars, "PWD"));
		free(vars->g_envv[i]);
		vars->g_envv[i] = ft_strdup(tmp);
		free(tmp);
	}
}

static int	check_access(char *path)
{
	int		ret;

	if ((ret=access(path, F_OK)) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(path);
		ft_putchar('\n');
	}
	else if ((ret=access(path, F_OK)) == -1)
	{
		ft_putstr("cd: permission denied: ");
		ft_putstr(path);
		ft_putchar('\n');
	}
	
	return (ret);
}

static void	cd_builtin(t_vars *vars, char	*newcwd)
{
	int		i;
	char	*tmp;

	if (!newcwd)
		return ;
	if (check_access(newcwd) == -1)
		return ;
	save_pwd(vars);
	i = get_var_index(vars, "PWD");
	if (i == -1)
		add_var(vars, "PWD", newcwd);
	else
	{
		tmp = ft_strdup("PWD");
		tmp = ft_strjoin(tmp,  "=");
		tmp = ft_strjoin(tmp, newcwd);
		free(vars->g_envv[i]);
		vars->g_envv[i] = ft_strdup(tmp);
		free(tmp);
	}
	
}

void	parse_cd(t_vars *vars, char **command)
{

	if (!command || !*command)
		return ;
	remove_quotes(&command[1]);
	if (!command[1])
		cd_builtin(vars, get_var(vars, "HOME"));
	else if (ft_strcmp(command[1],  "-") == 0)
		cd_builtin(vars, get_var(vars, "OLDPWD"));
	else if (command[1][0] == '$')
		cd_builtin(vars, get_var(vars, (command[1] + 1)));
	else
		cd_builtin(vars, command[1]);
}