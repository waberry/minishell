/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:31:34 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/11/21 17:34:11 by wdaher-a         ###   ########.fr       */
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

static char		**parse_input(char *user_input)
{
	char	**tmp;
	char	tmp_buff[1024];
	int		i;

	tmp = NULL;
	if (!user_input || !not_empty(user_input))
		return (tmp);
	tmp = ft_strsplit(user_input, '\t');
	ft_bzero(tmp_buff, 1024);
	i = 0;
	while (tmp && tmp[i])
	{
		ft_strcat(tmp_buff, tmp[i]);
		ft_strcat(tmp_buff, " ");
		++i;
	}
	if (tmp)
		free_tbl(tmp);
	tmp = ft_strsplit(tmp_buff, ' ');
	return (tmp);
}

static void		in_process_free(t_vars *vars)
{
	if (vars->user_input != NULL)
		free(vars->user_input);
	if (vars->commands != NULL)
		free_tbl(vars->commands);
	vars->commands = NULL;
	vars->user_input = NULL;
}

static void		handle_command(t_vars *vars, char **parsed_input)
{
	if (is_builtin(parsed_input))
		run_commands(parsed_input, vars);
	else
		parse_execute(vars, parsed_input);
	free_tbl(parsed_input);
	parsed_input = NULL;
}

int				main(int ac, char **av, char **env)
{
	char	**parsed_input;
	t_vars	*vars;
	int		i;

	vars = init_vars(env);
	while (1)
	{
		display_prompt_msg(vars, ac, av);
		get_next_line(0, &vars->user_input);
		if (not_empty(vars->user_input))
			vars->commands = ft_strsplit(vars->user_input, ';');
		i = -1;
		while (vars->commands != NULL && vars->commands[++i])
		{
			parsed_input = parse_input(vars->commands[i]);
			if (parsed_input != NULL)
				handle_command(vars, parsed_input);
		}
		in_process_free(vars);
	}
	return (0);
}
