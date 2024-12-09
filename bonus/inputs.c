/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:30:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/09 15:35:07 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

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
	if (!is_wall(cub->map.raw[(int)cub->player.pos.z]
			[(int)(npos.x + 0.1 * sign(move.x))]))
		cub->player.pos.x = npos.x;
	if (!is_wall(cub->map.raw[(int)(npos.z + 0.1 * sign(move.z))]
		[(int)cub->player.pos.x]))
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
	rotate(cub, cub->inputs[RARR] - cub->inputs[LARR]);
	if (cub->inputs[XK_space])
		act_ray(cub);
	if (cub->mouse_movement)
	{
		rotate(cub, (float) cub->mouse_movement * 0.05);
		cub->mouse_movement = 0;
		if (MOUSE_LOCK)
			mlx_mouse_move(cub->mlx, cub->win, SW / 2, SH / 2);
	}
}
