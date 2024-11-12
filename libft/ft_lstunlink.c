/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstunlink.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:27:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/11 13:27:55 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstunlink(t_list **lst, t_list *link)
{
	t_list	*first;

	if (!lst || !*lst)
		return ;
	first = *lst;
	if (first == link)
	{
		*lst = (*lst)->next;
		link->next = NULL;
		return ;
	}
	while (first && first->next && first->next != link)
		first = first->next;
	if (first->next && first->next == link)
	{
		first->next = link->next;
	}
	link->next = NULL;
}
