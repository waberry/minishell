/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: berry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:03:08 by berry             #+#    #+#             */
/*   Updated: 2019/09/29 21:33:43 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <limits.h>

typedef struct	s_vars
{
	char	**g_envv;
}				t_vars;

void			print_myenv(t_vars *vars);
char			**load_env_var(char **env);
char			*get_home_path(char **env, char *dest);
t_vars			*init_vars(char **env);
void			add_var(t_vars *vars, char *varname, char *value);
void			change_value(t_vars *vars, char **command);
void			parse_setenv(t_vars *vars, char **command);

int				get_tbl_len(char **tbl);
int				is_quote(char c);
void			*ft_realloc(void *ptr, size_t prev_size, size_t new_size);
char			*get_var(t_vars *vars, char *varname);
int				get_var_index(t_vars *vars, char *varname);
void			remove_quotes(char **s);
void			get_varname(char *var, char *tmp);
void			free_tbl(char **tbl);

void			display_prompt_msg(t_vars *vars);

void			echo_builtin(t_vars *vars, char *string, int no_newline);
void			parse_echo(t_vars *vars, char **command);

void			parse_unsetenv(t_vars *vars, char **command);

void			parse_cd(t_vars *vars, char **command);

void			bold_blue(void);
void			white(void);

int				run_commands(char **command, t_vars *vars);

int				is_builtin(char **command);
void			execute(t_vars *vars, char **command);
void			parse_execute(t_vars *vars, char **command);

void			exit_shell(t_vars *vars);
#endif
