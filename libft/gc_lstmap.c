/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga </var/spool/mail/bazaluga>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:48:16 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 18:48:38 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*gc_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*explorer;
	t_list	*head;

	explorer = (t_list *) malloc2(sizeof(t_list));
	if (!explorer)
		return (NULL);
	head = explorer;
	while (lst)
	{
		explorer->content = f(lst->content);
		if (lst->next)
		{
			explorer->next = (t_list *) malloc2(sizeof(t_list));
			if (!explorer->next)
			{
				gc_lstclear(&head, del);
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
