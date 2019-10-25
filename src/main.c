/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:31:34 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/10/14 17:32:54 by berry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			display_prompt_msg(t_vars *vars, int ac, char **av)
{
	ac = 0;
	av = NULL;
	bold_blue();
	ft_putstr(get_var(vars, "PWD"));
	white();
	ft_putstr(" \033[31m︻\033[0m\033[32m┳\033[0m\033[33mデ");
	ft_putstr("\033[0m\033[34m═\033[0m\033[35m—\033[0m$ ");
}

static char		**parse_input(t_vars *vars, char *user_input)
{
	char	**tmp;

	tmp = NULL;
	if (!empty(user_input))
		return (tmp);
	tmp = ft_strsplit(user_input, '\t');
	ft_bzero(user_input, ft_strlen(user_input));
	user_input = ft_memcpy(user_input, tmp[0], ft_strlen(tmp[0]));
	free_tbl(tmp);
	tmp = ft_strsplit(user_input, ' ');
	if (vars->hist == NULL)
		vars->hist = ft_lstnew(user_input, ft_strlen(user_input));
	else
		ft_lstadd(&vars->hist, ft_lstnew(user_input, ft_strlen(user_input)));
	return (tmp);
}

int				main(int ac, char **av, char **env)
{
	char	**parsed_input;
	t_vars	*vars;
	int		i;

	vars = NULL;
	vars = init_vars(env);
	while (1)
	{
		display_prompt_msg(vars, ac, av);
		get_next_line(0, &vars->user_input);
		vars->commands = ft_strsplit(vars->user_input, ';');
		i = 0;
		while (vars->commands[i])
		{
			parsed_input = parse_input(vars, vars->commands[i]);
			if (parsed_input != NULL)
			{
				if (is_builtin(parsed_input))
					run_commands(parsed_input, vars);
				else
					parse_execute(vars, parsed_input);
				if (parsed_input)
					free_tbl(parsed_input);
			}
			++i;
		}
		if (vars->commands)
			free_tbl(vars->commands);
		if (vars->user_input)
			free(vars->user_input);
	}
	return (0);
}
