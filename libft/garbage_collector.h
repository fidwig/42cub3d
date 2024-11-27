/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:03:21 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 12:40:12 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H
# include <stdlib.h>

typedef struct s_garbage
{
	void	*addr;
	void	(*free_fct)(void *);
}				t_garbage;

typedef struct s_trash	t_trash;

struct s_trash
{
	t_garbage	garbage;
	t_trash		*next;
};

// utils functions, do not use in your code
t_trash	*trash_add_garbage(t_trash **trash, void *addr, void (*fct)(void *));
int		trash_remove(t_trash **trash, void *addr);
int		trash_remove_node(t_trash **trash, t_trash *node);
t_trash	**get_trash(void);

// Functions to use
t_trash	*trash_add(void *addr, void (*free_fct)(void *));
void	*malloc2(size_t size);
void	free2(void *addr);
void	trash_clear(void);

#endif
