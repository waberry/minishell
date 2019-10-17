/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:24:12 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/09/29 20:27:38 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char **command)
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

void	execute(t_vars *vars, char **command)
{
	char			**path;
	int				j;
	char			buffer[PATH_MAX];
	pid_t			p_id;

	path = NULL;
	path = ft_strsplit(get_var(vars, "PATH"), ':');
	j = 0;
	ft_bzero(buffer, PATH_MAX);
	while (path[j] && path)
	{
		if (ft_strchr(command[0], '/') == NULL)
		{
			ft_memcpy(buffer, path[j], ft_strlen(path[j]));
			ft_strcat(buffer, "/");
			ft_strcat(buffer, command[0]);
		}
		else
			ft_strcpy(buffer, command[0]);
		if ((access(buffer, X_OK)) != -1)
		{
			if ((p_id = fork()) == 0)
				execve(buffer, command, vars->g_envv);
			wait(&p_id);
			//histore here !
			return ;
		}
		ft_bzero(buffer, PATH_MAX);
		++j;
	}
	ft_putstr("minishell: command not found: ");
	ft_putendl(command[0]);
	free_tbl(path);
}

void	parse_execute(t_vars *vars, char **command)
{
	int		i;
	char	*tmp;

	if (!command || !*command)
		return ;
	i = 1;
	while (command[i])
	{
		if (command[i] && command[i][0] == '\"')
			remove_quotes(&command[i]);
		if (command[i] && command[i][0] == '$')
		{
			tmp = ft_strdup((command[i] + 1));
			free(command[i]);
			command[i] = get_var(vars, tmp);
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
