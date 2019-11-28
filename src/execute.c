/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:24:12 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/11/21 19:03:55 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_builtin(char **command)
{
	if (ft_strcmp(command[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(command[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(command[0], "env") == 0)
		return (1);
	else if (ft_strcmp(command[0], "setenv") == 0)
		return (1);
	else if (ft_strcmp(command[0], "unsetenv") == 0)
		return (1);
	else if (ft_strcmp(command[0], "cd") == 0)
		return (1);
	else
		return (0);
}

static void	format_path(char *buffer, char *binname, char *path)
{
	ft_bzero(buffer, PATH_MAX);
	if (ft_strchr(binname, '/') == NULL)
	{
		ft_memcpy(buffer, path, ft_strlen(path));
		ft_strcat(buffer, "/");
		ft_strcat(buffer, binname);
	}
	else
		ft_strcpy(buffer, binname);
}

static int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (lstat(path, &path_stat) == -1)
		return (0);
	return (S_IFDIR & path_stat.st_mode);
}

void		execute(t_vars *vars, char **command)
{
	char			**path;
	int				j;
	char			buffer[PATH_MAX];
	pid_t			p_id;

	path = NULL;
	path = ft_strsplit(get_var(vars, "PATH"), ':');
	j = -1;
	while (path[++j] && path)
	{
		format_path(buffer, command[0], path[j]);
		if (!is_directory(buffer) && (access(buffer, X_OK)) != -1)
		{
			if ((p_id = fork()) == 0)
				execve(buffer, command, vars->g_envv);
			wait(&p_id);
			free_tbl(path);
			return ;
		}
	}
	ft_putstr("minishell: command not found: ");
	ft_putendl(command[0]);
	free_tbl(path);
}

/*
 ** Gerer les quotes que quand c'est pertinent
 ** pertinance = var_env,..ect test shell
 ** https://www.gnu.org/software/bash/manual/bash.html#Double-Quotes
*/
void		parse_execute(t_vars *vars, char **command)
{
	int		i;
	char	*tmp;

	if (!command || !*command)
		return ;
	i = 1;
	while (command[i])
	{
		if (command[i] && command[i][0] == '$')
		{
			tmp = ft_strdup((command[i] + 1));
			if (get_var(vars, tmp) != NULL)
			{
				free(command[i]);
				command[i] = ft_strdup(get_var(vars, tmp));
			}
			free(tmp);
		}
		if (ft_strcmp(command[i], "~") == 0)
		{
			free(command[i]);
			command[i] = ft_strdup(get_var(vars, "HOME"));
		}
		++i;
	}
	execute(vars, command);
}
