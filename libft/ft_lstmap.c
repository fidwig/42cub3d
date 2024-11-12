/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:35:31 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/10 21:48:51 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*explorer;
	t_list	*head;

	explorer = (t_list *) malloc(sizeof(t_list));
	if (!explorer)
		return (NULL);
	head = explorer;
	while (lst)
	{
		explorer->content = f(lst->content);
		if (lst->next)
		{
			explorer->next = (t_list *) malloc(sizeof(t_list));
			if (!explorer->next)
			{
				ft_lstclear(&head, del);
				return (NULL);
			}
		}
		else
			explorer->next = NULL;
		lst = lst->next;
		explorer = explorer->next;
	}
	return (head);
}
