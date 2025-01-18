/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:01:48 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/18 10:50:17 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

t_trash	*trash_add(void *addr, void (*free_fct)(void *))
{
	t_trash	*node;

	node = trash_add_garbage(get_trash(), addr, free_fct);
	return (node);
}

void	*malloc2(size_t size)
{
	void	*addr;

	addr = malloc(size);
	if (!addr)
		return (NULL);
	trash_add(addr, &free);
	return (addr);
}

void	free2(void *addr)
{
	if (addr)
		trash_remove(get_trash(), addr);
}

void	trash_clear(void)
{
	t_trash	**trash;

	trash = get_trash();
	if (!trash)
		return ;
	while (*trash)
		trash_remove_node(trash, *trash);
}
