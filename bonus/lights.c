/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:18:17 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/16 16:26:29 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

	// light = (LIGHT_RANGE - d) * LIGHT_STRENGTH;
	// light = (LIGHT_RANGE / 2) * pow(1 - d / LIGHT_RANGE, 3);
double	compute_light(double d)
{
	double	light;

	light = LIGHT_STRENGTH / (0.2 + d);
	return (light);
}

	// if (d < LIGHT_RANGE)[]
double	get_light(t_cub *cub, t_dvec3 tar)
{
	int		i;
	double	d;
	double	md;

	i = -1;
	md = dist((t_dvec3){cub->player.pos.x, cub->player.pos.z, 0}, tar);
	while (++i < cub->sprite_count)
	{
		if (!cub->sprites[i].light)
			continue ;
		d = dist(cub->sprites[i].pos, tar);
		if (d >= LIGHT_RANGE)
			continue ;
		if (d < md)
			md = d;
	}
	return (compute_light(md));
}
