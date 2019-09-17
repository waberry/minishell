/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 18:37:54 by wdaher-a          #+#    #+#             */
/*   Updated: 2018/07/02 19:52:56 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*ret;

	if (!lst || !f)
		return (NULL);
	new = ft_lstnew((*(f(lst))).content, (*(f(lst))).content_size);
	ret = new;
	if (!(lst->next))
		return (ret);
	while (lst->next)
	{
		lst = lst->next;
		new->next = (*f)(lst);
		new = new->next;
	}
	return (ret);
}
