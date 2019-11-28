/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 20:34:16 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/11/28 20:34:18 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_directory(const char *path)
{
	struct stat	path_stat;

	if (lstat(path, &path_stat) == -1)
		return (0);
	return (S_IFDIR & path_stat.st_mode);
}

void	exec_without_path(char *bin_path, char **command, t_vars *vars)
{
	pid_t			p_id;

	if (!is_directory(bin_path) && (access(bin_path, X_OK)) != -1)
	{
		if ((p_id = fork()) == 0)
			execve(bin_path, command, vars->g_envv);
		wait(&p_id);
		return ;
	}
	ft_putstr("minishell: command not found: ");
	ft_putendl(command[0]);
}
