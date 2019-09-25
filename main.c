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



void	display_prompt_msg(t_vars *vars)
{
	bold_blue();
	ft_putstr(vars->cwd);
	white();
	ft_putstr(" \033[31m︻\033[0m\033[32m┳\033[0m\033[33mデ");
	ft_putstr("\033[0m\033[34m═\033[0m\033[35m—\033[0m$ ");
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

int		is_builtin(char *command)
{
	if (ft_strcmp(command[0], "exit") ==  0)
		return (1)
	else if (ft_strcmp(command[0], "echo") == 0)
		return (1)
	else if (ft_strcmp(command[0], "env") == 0)
		return (1)
	else if (ft_strcmp(command[0], "setenv") == 0)
		return (1)
	else if (ft_strcmp(command[0], "unsetenv") == 0)
		return (1)
	else if (ft_strcmp(command[0], "cd") == 0)
		return (1)
	else
		return (0);
}

int		main(int ac, char **av, char **env)
{
	char *user_input;
	char **parsed_input;
	t_vars	*vars;

	vars = NULL;
	vars = init_vars(env);
	if (ac || !ac)
		ft_putendl("testing ac");
	if (av || !av)
		ft_putendl("testing av");
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
				//run non builtin command
				//if ()
				//execve(parsed_input[0], av, env);
			}	
			free_tbl(parsed_input);
		}
	}
	return (0);
}
