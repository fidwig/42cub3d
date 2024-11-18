/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:56:09 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 12:59:14 by bazaluga         ###   ########.fr       */
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
		ft_lstdelone2(first, del);
		return ;
	}
	while (first && first->next && first->next != link)
		first = first->next;
	if (first->next && first->next == link)
	{
		first->next = link->next;
		ft_lstdelone2(link, del);
	}
}
