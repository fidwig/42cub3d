/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:30:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/13 23:19:25 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	wrap_angle(double angle)
{
	if (angle >= 2.0 * M_PI)
		angle -= 2.0 * M_PI;
	else if (angle < 0)
		angle += 2.0 * M_PI;
	return (angle);
}

void	rotate(t_cub *cub, int r)
{
	if (!r)
		return ;
	cub->player.rot = wrap_angle(cub->player.rot
			+ ((double)r * (M_PI / 8.0) * cub->info.delta / 100));
}

void	move(t_cub *cub, int x, int y)
{
	t_dvec3	move;

	if (x == 0 && y == 0)
		return ;

	move.x = x * cos(cub->player.rot + (M_PI / 2.0)) + y * cos(cub->player.rot);
	move.z = x * sin(cub->player.rot + (M_PI / 2.0)) + y * sin(cub->player.rot);
	move.x *= cub->player.spd * (cub->info.delta / 100.0);
	move.z *= cub->player.spd * (cub->info.delta / 100.0);

	//check for collisions

	cub->player.pos.x += move.x;
	cub->player.pos.z += move.z;
}

void	inputs_handler(t_cub *cub)
{
	move(cub, cub->inputs[XK_d] - cub->inputs[XK_a],
		cub->inputs[XK_w] - cub->inputs[XK_s]);
	rotate(cub, cub->inputs[RARR] - cub->inputs[LARR]);
}
