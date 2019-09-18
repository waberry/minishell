/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: berry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:21:00 by berry             #+#    #+#             */
/*   Updated: 2019/07/25 17:43:38 by berry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bold_blue(void)
{
	ft_putstr("\e[1;36m");
}

void	white(void)
{
	ft_putstr("\e[0m");
}

void	display_prompt_msg(t_vars *vars)
{
	bold_blue();
	ft_putstr(vars->cwd);
	//ft_putchar(' ');
	white();
	ft_putstr(" \033[31m︻\033[0m\033[32m┳\033[0m\033[33mデ");
	ft_putstr("\033[0m\033[34m═\033[0m\033[35m—\033[0m$ ");
}

void	exit_shell(t_vars *vars)
{
	free_tbl(vars->g_envv);
	free(vars);
	write(1, "\n", 1);
	exit(0);
}

void		run_commands(char **command, t_vars *vars)
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
		ft_putstr("minishell: command not found: ")
		ft_putendl(command[0]);
		return;
	}
}

void		get_input(char **input, t_vars *vars)
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

int		main(int argc, char **argv, char **env)
{
	char *user_input;
	char **parsed_input;
	t_vars	*vars;

	vars = NULL;
	vars = init_vars(env);
	if (argc || !argc)
		ft_putendl("testing argc");
	if (argv || !argv)
		ft_putendl("testing argv");
	while (1)
	{
		display_prompt_msg(vars);
		get_input(&user_input, vars);
		if (user_input)
		{
			parsed_input = ft_strsplit(user_input, ' ');
			free(user_input);
			run_commands(parsed_input, vars);
			free_tbl(parsed_input);
		}
	}
	return (0);
}
