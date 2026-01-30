/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 23:48:49 by ssivilay          #+#    #+#             */
/*   Updated: 2025/11/19 11:37:05 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*tmp;
	void	*tmp_content;

	if (!lst || !f)
		return (NULL);
	res = NULL;
	while (lst)
	{
		tmp_content = f(lst->content);
		tmp = ft_lstnew(tmp_content);
		if (!tmp)
		{
			if (del)
				del(tmp_content);
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, tmp);
		lst = lst->next;
	}
	return (res);
}
