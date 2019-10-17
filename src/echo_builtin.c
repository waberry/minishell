/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:22:25 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/09/29 20:24:07 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_putstr_newline(char *s, int no_newline)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '\n' && no_newline)
			ft_putchar(s[i]);
		else
			ft_putchar(s[i]);
		++i;
	}
}

void			echo_builtin(t_vars *vars, char *string, int no_newline)
{
	char	*tmp;

	if (string[0] == '\"' && string[1] == '$')
		remove_quotes(&(string));
	if (string[0] == '$')
	{
		tmp = get_var(vars, (string + 1));
		if (!tmp || ft_strcmp(tmp, "@") == 0)
			ft_putstr_newline("", no_newline);
		else
			ft_putstr_newline(tmp, no_newline);
	}
	else if (ft_strcmp(string, "~") == 0)
		ft_putstr_newline(get_var(vars, "HOME"), no_newline);
	else
		ft_putstr_newline(string, no_newline);
}

void			parse_echo(t_vars *vars, char **command)
{
	int		i;

	if (!command || !*command)
		return ;
	if (command[1])
	{
		i = (ft_strcmp(command[1], "-n") == 0) ? 2 : 1;
		while (command[i])
		{
			if (ft_strcmp(command[1], "-n") == 0)
				echo_builtin(vars, (char*)command[i], 1);
			else
				echo_builtin(vars, (char*)command[i], 0);
			if (command[i + 1])
				ft_putchar(' ');
			++i;
		}
		if (ft_strcmp(command[1], "-n") != 0)
			ft_putchar('\n');
	}
}