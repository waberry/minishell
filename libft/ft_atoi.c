/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:56:22 by wdaher-a          #+#    #+#             */
/*   Updated: 2018/07/10 19:54:54 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	size_t				i;
	long long int		neg;
	unsigned long int	nbr;

	nbr = 0;
	neg = 0;
	i = 0;
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == '\v') ||
			(str[i] == ' ') || (str[i] == '\f') || (str[i] == '\r'))
		++i;
	if (str[i] == '-')
		neg = 1;
	if (str[i] == '+' || str[i] == '-')
		++i;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nbr *= 10;
		nbr += (int)str[i] - '0';
		++i;
		if (nbr > 9223372036854775807)
			return ((neg) ? 0 : -1);
	}
	if (neg)
		nbr = -1 * nbr;
	return (nbr);
}
