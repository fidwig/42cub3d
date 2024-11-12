/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:54:53 by jsommet           #+#    #+#             */
/*   Updated: 2023/11/17 20:12:04 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tofree;

	if (!lst || !del)
		return ;
	while ((*lst))
	{
		tofree = *lst;
		*lst = (*lst)->next;
		del(tofree->content);
		free(tofree);
	}
}
