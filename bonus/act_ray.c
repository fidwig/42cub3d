/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:37:31 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/26 15:11:45 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

	// t_ray		ray;
	// t_dvec3		ray_dir;

	// ray_dir = (t_dvec3){cos(cub->player.rot), sin(cub->player.rot), 0};
	// ray = cast_ray(cub->player.pos, ray_dir, cub->map);
	// if (ray.length > 1)
		// return ;
	// printf("%d %d %c\n", ray.info.pos.x, ray.info.pos.y, ray.info.type);
	// if (ray.info.type == 'D')
		// cub->map.raw[ray.info.pos.y][ray.info.pos.x] = 'O';
	// if (ray.info.type == 'O')
		// cub->map.raw[ray.info.pos.y][ray.info.pos.x] = 'D';
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
