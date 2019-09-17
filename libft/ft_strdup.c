/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <wdaher@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 17:23:40 by wdaher-a          #+#    #+#             */
/*   Updated: 2018/07/03 18:09:46 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	len;
	int		i;

	len = ft_strlen(s1);
	if (!(res = (char *)malloc(sizeof(char) * len + 1)))
	{
		errno = ENOMEM;
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		++i;
	}
	res[i] = '\0';
	return (res);
}
