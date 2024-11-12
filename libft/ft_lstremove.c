/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:28:02 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/11 13:28:02 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove(t_list **lst, t_list *link, void (*del)(void *))
{
	t_list	*first;

	if (!lst || !*lst)
		return ;
	first = *lst;
	if (first == link)
	{
		*lst = (*lst)->next;
		ft_lstdelone(first, del);
		return ;
	}
	while (first && first->next && first->next != link)
		first = first->next;
	if (first->next && first->next == link)
	{
		first->next = link->next;
		ft_lstdelone(link, del);
	}
}
