/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_get_maxstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:48:09 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/28 08:57:52 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	lst_get_maxstr(t_list *lst)
{
	size_t	max;
	size_t	tmp;

	if (!lst || (lst && !lst->content))
		return (0);
	max = ft_strlen((const char *)lst->content);
	lst = lst->next;
	while (lst && lst->content)
	{
		tmp = ft_strlen((const char *)lst->content);
		if (tmp > max)
			max = tmp;
		lst = lst->next;
	}
	return (max);
}
