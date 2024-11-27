/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga </var/spool/mail/bazaluga>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:39:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 18:47:58 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	gc_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tofree;

	if (!lst)
		return ;
	while (*lst)
	{
		tofree = *lst;
		*lst = (*lst)->next;
		gc_lstdelone(tofree, del);
	}
	*lst = NULL;
}
