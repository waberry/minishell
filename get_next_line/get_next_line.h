/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 23:03:14 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/10/18 16:10:24 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 8
# include "../libft/libft.h"
# include <limits.h>
# include <string.h>
# include <unistd.h>

int		get_next_line(int const fd, char **line);

#endif
