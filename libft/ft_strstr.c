/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 18:22:15 by wdaher-a          #+#    #+#             */
/*   Updated: 2018/07/03 21:20:50 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	len_needle;

	if (!(ft_strcmp(haystack, needle)) || ft_strlen(needle) == 0)
		return ((char *)haystack);
	else if (!ft_strlen(haystack))
		return (NULL);
	len_needle = ft_strlen(needle);
	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (haystack[i + j] == needle[j] && j < len_needle)
				++j;
			if (j == len_needle)
				return ((char *)haystack + i);
		}
		++i;
	}
	return (NULL);
}
