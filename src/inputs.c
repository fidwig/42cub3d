/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:30:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/04 09:36:11 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "typedefs.h"

void	rotate(t_cub *cub, float r)
{
	if (!r)
		return ;
	cub->player.rot = wrap_angle(cub->player.rot
			+ ((double)r * (M_PI / 10.0) * cub->info.delta / 100.0));
}

double	sign(double n)
{
	if (n < 0)
		return (-1);
	else
		return (1);
}

void	move(t_cub *cub, int x, int y)
{
	t_dvec3	move;
	t_dvec3	npos;
	double	mangle;

	if (x == 0 && y == 0)
		return ;
	mangle = wrap_angle(cub->player.rot + atan2(x, y));
	move.x = cos(mangle) * cub->player.spd * (cub->info.delta / 1000.0);
	move.z = sin(mangle) * cub->player.spd * (cub->info.delta / 1000.0);
	npos.x = cub->player.pos.x + move.x;
	npos.z = cub->player.pos.z + move.z;
	if (cub->map.raw[(int)cub->player.pos.z]
		[(int)(npos.x + 0.1 * sign(move.x))] != '1')
		cub->player.pos.x = npos.x;
	if (cub->map.raw[(int)(npos.z + 0.1 * sign(move.z))]
		[(int)cub->player.pos.x] != '1')
		cub->player.pos.z = npos.z;
}
// move.x = x * cos(cub->player.rot + (M_PI / 2.0)) + y * cos(cub->player.rot);
// move.z = x * sin(cub->player.rot + (M_PI / 2.0)) + y * sin(cub->player.rot);
// move.x *= cub->player.spd * (cub->info.delta / 100.0);
// move.z *= cub->player.spd * (cub->info.delta / 100.0);dis

void	inputs_handler(t_cub *cub)
{
	move(cub, cub->inputs[XK_d] - cub->inputs[XK_a],
		cub->inputs[XK_w] - cub->inputs[XK_s]);
	rotate(cub, (cub->inputs[RARR] - cub->inputs[LARR]));
}
