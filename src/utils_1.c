
#include "minishell.h"

int		get_tbl_len(char **tbl)
{
	int		count;

	count = 0;
	while (tbl[count])
		++count;
	return (count);
}

int		is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size)
{
	void	*new;

	if (!ptr)
		return (NULL);
	if (!(new = ft_memalloc(new_size)))
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(new, ptr, prev_size < new_size ? prev_size : new_size);
	free(ptr);
	return (new);
}

void	get_varname(char *var, char *tmp)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return ;
		tmp[i] = var[i];
		++i;
	}
}

int		get_var_index(t_vars *vars, char *varname)
{
	int		i;
	char	tmp[1024];

	i = 0;
	while (vars->g_envv[i])
	{
		get_varname(vars->g_envv[i], tmp);
		if (ft_strcmp(tmp, varname) == 0)
			return (i);
		else
			ft_bzero(tmp, 1024);
		++i;
	}
	return (-1);
}