/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 23:02:57 by wdaher-a          #+#    #+#             */
/*   Updated: 2018/12/08 16:15:30 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*biggerbuf(int const fd, char *buf, int *ret)
{
	char	tmp[BUFF_SIZE + 1];
	char	*tmp2;

	*ret = read(fd, tmp, BUFF_SIZE);
	if (*ret > 0 && *ret < BUFF_SIZE && tmp[*ret - 1] != '\n')
	{
		tmp[*ret] = '\n';
		tmp[*ret + 1] = '\0';
	}
	else
		tmp[*ret] = '\0';
	tmp2 = buf;
	buf = ft_strjoin(buf, tmp);
	ft_strdel(&tmp2);
	return (buf);
}

static void	store_line(char *str, char **line, char **buf)
{
	*str = 0;
	*line = ft_strdup(*buf);
	ft_memmove(*buf, str + 1, ft_strlen(str + 1) + 1);
}

static void	line_saver(char **buf, int *ret)
{
	ft_strdel(buf);
	*ret = 1;
}

int			get_next_line(int const fd, char **line)
{
	static char		*buf[OPEN_MAX];
	int				ret;
	char			*str;

	if (!line || fd < 0 || fd >= OPEN_MAX || read(fd, buf[fd], 0) == -1)
		return (-1);
	ret = 1;
	buf[fd] = (!buf[fd]) ? ft_strnew(0) : buf[fd];
	while (ret > 0)
	{
		if (!(buf[fd] = biggerbuf(fd, buf[fd], &ret)))
			return (-1);
		if ((str = ft_strchr(buf[fd], '\n')) != NULL)
		{
			store_line(str, line, &buf[fd]);
			return (1);
		}
	}
	if (ret == 0 && ft_strlen(buf[fd]) > 0)
	{
		if (!(*line = ft_strdup(buf[fd])))
			return (-1);
		line_saver(&buf[fd], &ret);
	}
	return (ret);
}
