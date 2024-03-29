/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: berry <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:03:08 by berry             #+#    #+#             */
/*   Updated: 2019/10/14 16:57:18 by berry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <limits.h>


typedef struct	s_vars
{
	char	**g_envv;
	t_list	*hist;
	char	*user_input;
	char	**commands;
}				t_vars;

void			print_myenv(t_vars *vars);
char			**load_env_var(char **env);
t_vars			*init_vars(char **env);
void			add_var(t_vars *vars, char *varname, char *value);
void			change_value(t_vars *vars, char **command);
void			parse_setenv(t_vars *vars, char **command);

int				get_tbl_len(char **tbl);
char			*get_var(t_vars *vars, char *varname);
int				get_var_index(t_vars *vars, char *varname);
void			remove_quotes(char **s);
void			get_varname(char *var, char *tmp);
void			free_tbl(char **tbl);
int				ft_strchri_last(const char *s, int c);
int				not_empty(char *s);
void			*ft_realloc(void *ptr, size_t prev_size, size_t new_size);

void			display_prompt_msg(t_vars *vars, int ac, char **av);

void			echo_builtin(t_vars *vars, char *string, int no_newline);
void			parse_echo(t_vars *vars, char **command);

void			parse_unsetenv(t_vars *vars, char **command);

void			cd_builtin(t_vars *vars, char *newcwd);
void			parse_cd(t_vars *vars, char **command);

void			bold_blue(void);
void			white(void);

void			display_prompt_msg(t_vars *vars, int ac, char **av);
void			get_input(char **input);

int				run_commands(char **command, t_vars *vars);
void			exec_without_path(char *bin_path, char **command, t_vars *vars);
int				is_directory(const char *path);

int				is_builtin(char **command);
void			execute(t_vars *vars, char **command);
void			parse_execute(t_vars *vars, char **command);

void			exit_shell(t_vars *vars);
#endif
