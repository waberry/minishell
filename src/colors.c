/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:32:11 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/09/29 18:32:22 by wdaher-a         ###   ########.fr       */
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
