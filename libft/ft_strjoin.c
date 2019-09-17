/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 18:59:41 by wdaher-a          #+#    #+#             */
/*   Updated: 2018/07/03 19:03:09 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	res_len;
	size_t	j;
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	res_len = (size_t)ft_strlen((char *)s1) + (size_t)ft_strlen((char *)s2);
	if (!(res = (char *)malloc(sizeof(char) * res_len)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		res[i] = s2[j];
		++i;
		++j;
	}
	res[i] = '\0';
	return (res);
}
