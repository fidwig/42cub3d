/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga </var/spool/mail/bazaluga>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:18 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 18:49:34 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove2(t_list **lst, t_list *link, void (*del)(void *))
{
	t_list	*first;

	if (!lst || !*lst)
		return ;
	first = *lst;
	if (first == link)
	{
		*lst = (*lst)->next;
		gc_lstdelone(first, del);
		return ;
	}
	while (first && first->next && first->next != link)
		first = first->next;
	if (first->next && first->next == link)
	{
		first->next = link->next;
		gc_lstdelone(link, del);
	}
}
