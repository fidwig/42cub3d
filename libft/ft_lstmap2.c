/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:54:03 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 12:59:01 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap2(t_list *lst, void *(*f)(void *), void (*del)(void *))
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
				ft_lstclear2(&head, del);
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
