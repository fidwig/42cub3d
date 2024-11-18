/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:22:10 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 10:34:23 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <stdlib.h>

t_trash	*trash_add_garbage(t_trash **trash, void *addr, void (*fct)(void *))
{
	t_trash	*new;
	t_trash	*last;

	if (!trash)
		return (NULL);
	new = malloc(sizeof(t_trash));
	if (!new)
		return (NULL);
	new->garbage.addr = addr;
	new->garbage.free_fct = fct;
	new->next = NULL;
	if (!*trash)
		return (*trash = new, new);
	last = *trash;
	while (last->next)
		last = last->next;
	last->next = new;
	return (new);
}

int	trash_remove(t_trash **trash, void *addr)
{
	t_trash	*node;
	t_trash	*tofree;

	if (!trash)
		return (0);
	if (*trash && (*trash)->garbage.addr == addr)
	{
		tofree = *trash;
		*trash = (*trash)->next;
		tofree->garbage.free_fct(addr);
		free(tofree);
		return (1);
	}
	node = *trash;
	while (node && node->next && node->next->garbage.addr != addr)
		node = node->next;
	if (node->next && node->next->garbage.addr == addr)
		tofree = node->next;
	else
		return (0);
	node->next = tofree->next;
	tofree->garbage.free_fct(addr);
	free(tofree);
	return (1);
}

int	trash_remove_node(t_trash **trash, t_trash *node)
{
	t_trash	*prev;

	if (!trash)
		return (0);
	if (*trash == node)
	{
		*trash = (*trash)->next;
		node->garbage.free_fct(node->garbage.addr);
		free(node);
		return (1);
	}
	prev = *trash;
	while (prev && prev->next && prev->next != node)
		prev = prev->next;
	prev->next = node->next;
	node->garbage.free_fct(node->garbage.addr);
	free(node);
	return (1);
}

t_trash	**get_trash(void)
{
	static t_trash	*trash;

	return (&trash);
}
