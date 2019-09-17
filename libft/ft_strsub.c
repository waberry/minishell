/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 18:56:44 by wdaher-a          #+#    #+#             */
/*   Updated: 2018/07/03 18:56:59 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	if (s == NULL || start > (unsigned int)ft_strlen((char *)s))
		return (NULL);
	if (!(res = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		res[i] = s[start];
		++i;
		++start;
	}
	res[i] = '\0';
	return (res);
}
