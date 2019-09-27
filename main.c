/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: berry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:21:00 by berry             #+#    #+#             */
/*   Updated: 2019/09/27 21:14:45 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt_msg(t_vars *vars)
{
	bold_blue();
	ft_putstr(vars->cwd);
	white();
	ft_putstr(" \033[31m︻\033[0m\033[32m┳\033[0m\033[33mデ");
	ft_putstr("\033[0m\033[34m═\033[0m\033[35m—\033[0m$ ");
}

void	get_input(char **input, t_vars *vars)
{
	int		ret;
	char	buf;
	int		i;
	int		count;

	*input = ft_strnew(1);
	count = 1;
	i = 0;
	while ((ret = read(0, &buf, 1)) && buf != '\n')
	{
		*(*input + i++) = buf;
		*input = ft_realloc(*input, count, count + 1);
		count++;
	}
	*(*input + i) = '\0';
	if (!ret)
	{
		free(*input);
		exit_shell(vars);
	}
}

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
	char			*tmp;
	pid_t			p_id;

	path = NULL;
	tmp = get_var(vars, "PATH");
	path = ft_strsplit(tmp, ':');
	j = 0;
	free(tmp);
	tmp = NULL;
	while (path[j] && path)
	{
		ft_memcpy(buffer, path[j], ft_strlen(path[j]));
		ft_strcat(buffer, "/");
		ft_strcat(buffer, command[0]);
		if ((access(buffer, F_OK)) != -1)
		{
			p_id = fork();
			//handle ~ and $
			if (p_id == 0)
				execve(buffer, command, vars->g_envv);
			wait(&p_id);
			return ;
		}
		ft_bzero(buffer, PATH_MAX);
		++j;
	}
	ft_putstr("minishell: command not found: ");
	ft_putendl(command[0]);
	
}

int		main(int ac, char **av, char **env)
{
	char *user_input;
	char **parsed_input;
	t_vars	*vars;

	vars = NULL;
	vars = init_vars(env);
	av = NULL;
	ac = 0;
	while (1)
	{
		display_prompt_msg(vars);
		get_input(&user_input, vars);
		if (user_input)
		{
			parsed_input = ft_strsplit(user_input, ' ');
			free(user_input);
			if (is_builtin(parsed_input))
				run_commands(parsed_input, vars);
			else
			{
				execute(vars, parsed_input);
			}	
			free_tbl(parsed_input);
		}
	}
	return (0);
}
