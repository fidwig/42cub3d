/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:54:53 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/18 09:13:26 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tofree;

	if (!lst)
		return ;
	while (*lst)
	{
		tofree = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(tofree, del);
	}
	*lst = NULL;
}
