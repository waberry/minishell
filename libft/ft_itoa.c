/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 16:12:52 by wdaher-a          #+#    #+#             */
/*   Updated: 2018/08/22 17:31:53 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nlen(int n)
{
	int		len;
	int		tmp;

	len = 0;
	tmp = (n > 0) ? n : -n;
	while (tmp)
	{
		len++;
		tmp /= 10;
	}
	return (len);
}

static void	putend(char *str, size_t len, int n)
{
	if (n < 0)
		str[len] = '\0';
	else
		str[len + 1] = '\0';
}

char		*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		n_len;

	n_len = nlen(n);
	if (!(res = ft_strnew(n_len + 1)))
		return (NULL);
	i = (n < 0) ? n_len : n_len - 1;
	putend(res, n_len, n);
	if (n < 0)
	{
		if (n == INT_MIN)
			return (ft_strdup("-2147483648"));
		res[0] = '-';
		n *= -1;
	}
	while (i > -1)
	{
		if (res[i] != '-')
			res[i] += '0' + n % 10;
		n = n / 10;
		--i;
	}
	return (!(ft_strlen(res)) ? ft_memcpy(res, "0", 1) : res);
}
