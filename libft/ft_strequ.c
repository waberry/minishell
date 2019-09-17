/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 19:00:53 by wdaher-a          #+#    #+#             */
/*   Updated: 2018/07/03 19:02:31 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (0);
	len1 = 0;
	while (s1[len1])
		++len1;
	len2 = 0;
	while (s2[len2])
		++len2;
	if (len1 != len2)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		++i;
	}
	return (1);
}
