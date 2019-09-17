/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:11:08 by wdaher-a          #+#    #+#             */
/*   Updated: 2018/10/15 12:18:02 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')))
			++count;
		++i;
	}
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	start;
	size_t	end;
	char	**ptr;
	int		i;

	start = 0;
	end = 0;
	i = 0;
	ptr = NULL;
	if (!s ||
	!(ptr = (char **)ft_memalloc(sizeof(char *) * (count_words(s, c) + 1))))
		return (ptr);
	while (count_words(s, c) - i)
	{
		while (s && *(s + start) && *(s + start) == c)
			start++;
		while (s && *(s + start + end) && *(s + start + end) != c)
			end++;
		ptr[i] = ft_strsub(s, start, end);
		start += end;
		end = 0;
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
