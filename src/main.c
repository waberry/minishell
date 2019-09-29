/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:31:34 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/09/29 18:31:39 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt_msg(t_vars *vars)
{
	bold_blue();
	ft_putstr(get_var(vars, "PWD"));
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

int		main(int ac, char **av, char **env)
{
	char	*user_input;
	char	**parsed_input;
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
				parse_execute(vars, parsed_input);
			free_tbl(parsed_input);
		}
	}
	return (0);
}