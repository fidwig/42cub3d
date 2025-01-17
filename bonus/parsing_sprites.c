/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:40:14 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/17 13:05:54 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	save_sprite(t_pars_data *d, int row, int col)
{
	t_sprite	*new;
	int			n_sprite;

	new = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
	if (!new)
		return (0);
	if (!ft_lstadd_back(&d->lstsprites, ft_lstnew(new)))
		return (0);
	n_sprite = ft_strchr(d->names, d->line[col]) - d->names;
	new->name = d->names[n_sprite];
	new->tex = d->sprites[n_sprite].tex;
	new->pos = (t_dvec3){col + 0.5, row + 0.5, 0};
	new->light = d->sprites[n_sprite].light;
	d->line[col] = '0';
	d->n_sprites++;
	return (1);
}

int	lst_to_sprites(t_cub *cub, t_pars_data *d)
{
	t_list	*node_next;
	int		i;

	cub->sprites = (t_sprite *)ft_calloc(d->n_sprites, sizeof(t_sprite));
	if (!cub->sprites)
		return (6);
	i = 0;
	while (d->lstsprites && i < d->n_sprites)
	{
		node_next = d->lstsprites->next;
		cub->sprites[i] = *((t_sprite*)(d->lstsprites->content));
		free(d->lstsprites->content);
		free(d->lstsprites);
		d->lstsprites = node_next;
		i++;
	}
	cub->sprite_count = i;
	return (0);
}
