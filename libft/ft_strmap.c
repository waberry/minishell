/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 18:58:41 by wdaher-a          #+#    #+#             */
/*   Updated: 2018/07/03 18:59:03 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*res;
	size_t	len;

	if (!s || !f)
		return (NULL);
	len = 0;
	while (s[len])
		++len;
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = (*f)(s[i]);
		++i;
	}
	res[i] = '\0';
	return (res);
}
