/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:55:06 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 12:58:34 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear2(t_list **lst, void (*del)(void *))
{
	t_list	*tofree;

	if (!lst)
		return ;
	while (*lst)
	{
		tofree = *lst;
		*lst = (*lst)->next;
		ft_lstdelone2(tofree, del);
	}
	*lst = NULL;
}
