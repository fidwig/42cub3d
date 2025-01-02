/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:37:31 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/04 09:39:51 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	act_ray(t_cub *cub)
{
	int						x;
	int						y;
	static unsigned long	last;
	char					*cell;

	if (cub->info.last_frame - last < 250)
		return ;
	x = (int)(cub->player.pos.x + cos(cub->player.rot));
	y = (int)(cub->player.pos.z + sin(cub->player.rot));
	if (x == (int)cub->player.pos.x && y == (int)cub->player.pos.z)
		return ;
	cell = &cub->map.raw[y][x];
	if (*cell == 'D')
		*cell = 'O';
	else if (*cell == 'O')
		*cell = 'D';
	last = cub->info.last_frame;
}
