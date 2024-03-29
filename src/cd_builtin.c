/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:32:42 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/10/28 19:48:08 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		tilde_handler(t_vars *vars, char *tilded_path)
{
	char	tmp_buff[PATH_MAX];

	if (!tilded_path || ft_strlen(tilded_path) <= 1 || tilded_path[0] != '~')
		return ;
	ft_bzero(tmp_buff, PATH_MAX);
	ft_memcpy(tmp_buff, get_var(vars, "HOME"),
		ft_strlen(get_var(vars, "HOME")));
	ft_strcat(tmp_buff, (tilded_path + 1));
	ft_bzero(tilded_path, PATH_MAX);
	ft_memcpy(tilded_path, tmp_buff, ft_strlen(tmp_buff));
	ft_bzero(tmp_buff, PATH_MAX);
}

static void		save_pwd(t_vars *vars)
{
	int		i;
	char	tmp[PATH_MAX];

	i = get_var_index(vars, "OLDPWD");
	ft_bzero(tmp, PATH_MAX);
	if (i == -1)
		add_var(vars, "OLDPWD", get_var(vars, "PWD"));
	else
	{
		ft_strcat(tmp, "OLDPWD=");
		ft_strcat(tmp, get_var(vars, "PWD"));
		free(vars->g_envv[i]);
		vars->g_envv[i] = ft_strdup(tmp);
	}
}

static int		check_access(char *path)
{
	int		ret;

	if ((ret = access(path, F_OK)) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(path);
		ft_putchar('\n');
	}
	else if ((ret = access(path, R_OK)) == -1)
	{
		ft_putstr("cd: permission denied: ");
		ft_putstr(path);
		ft_putchar('\n');
	}
	else if ((ret = access(path, X_OK)) == -1)
	{
		ft_putstr("cd: not a directory: ");
		ft_putstr(path);
		ft_putchar('\n');
	}
	return (ret);
}

void			cd_builtin(t_vars *vars, char *newcwd)
{
	int		i;
	char	tmp[PATH_MAX];
	char	cwd[PATH_MAX];

	ft_bzero(tmp, PATH_MAX);
	ft_bzero(cwd, PATH_MAX);
	if (!newcwd)
		return ;
	ft_strcat(cwd, newcwd);
	if (check_access(cwd) == -1)
		return ;
	save_pwd(vars);
	i = get_var_index(vars, "PWD");
	if (i == -1)
		add_var(vars, "PWD", cwd);
	else
	{
		chdir(cwd);
		getcwd(cwd, PATH_MAX);
		ft_strcat(tmp, "PWD=");
		ft_strcat(tmp, cwd);
		free(vars->g_envv[i]);
		vars->g_envv[i] = ft_strdup(tmp);
		ft_bzero(tmp, PATH_MAX);
	}
}

void			parse_cd(t_vars *vars, char **command)
{
	char	tmp_buff1[PATH_MAX];

	ft_bzero(tmp_buff1, PATH_MAX);
	if (!command || !*command)
		return ;
	if (command[1] && command[1][0] == '\"')
		remove_quotes(&command[1]);
	if (command[1] == NULL || (ft_strcmp(command[1], "~") == 0))
		cd_builtin(vars, get_var(vars, "HOME"));
	else if ((ft_strcmp(command[1], "-")) == 0)
		cd_builtin(vars, get_var(vars, "OLDPWD"));
	else if (command[1][0] == '$')
		cd_builtin(vars, get_var(vars, (command[1] + 1)));
	else if (ft_strcmp(command[1], "..") == 0)
	{
		ft_memcpy(tmp_buff1, get_var(vars, "PWD"),
			ft_strchri_last(get_var(vars, "PWD"), '/'));
		cd_builtin(vars, tmp_buff1);
	}
	else
	{
		ft_strcat(tmp_buff1, command[1]);
		tilde_handler(vars, tmp_buff1);
		cd_builtin(vars, tmp_buff1);
	}
}
