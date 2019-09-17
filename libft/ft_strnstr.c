/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 18:23:09 by wdaher-a          #+#    #+#             */
/*   Updated: 2018/07/03 21:20:17 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_little;

	if (!(ft_strcmp(big, little)) || ft_strlen(little) == 0)
		return ((char *)big);
	else if (!ft_strlen(big))
		return (NULL);
	len_little = ft_strlen(little);
	i = 0;
	while (i < len && big[i])
	{
		if (big[i] == little[0])
		{
			j = 0;
			while ((i + j) < len && big[i + j] == little[j] && j < len_little)
				++j;
			if (j == len_little)
				return ((char *)big + i);
		}
		++i;
	}
	return (NULL);
}
