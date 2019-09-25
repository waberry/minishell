#include "minishell.h"

void	bold_blue(void)
{
	ft_putstr("\e[1;36m");
}

void	white(void)
{
	ft_putstr("\e[0m");
}