/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:18:17 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/18 11:45:48 by bazaluga         ###   ########.fr       */
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
double	get_light(t_cub *cub, t_dvec3 tar, double light)
{
	int		i;
	double	tl;
	double	d;

	i = -1;
	d = dist((t_dvec3){cub->player.pos.x, cub->player.pos.z, 0}, tar);
	light = compute_light(d);
	while (++i < cub->sprite_count)
	{
		if (!cub->sprites[i].light)
			continue ;
		d = dist(cub->sprites[i].pos, tar);
		if (d >= LIGHT_RANGE)
			continue ;
		tl = compute_light(d);
		if (tl > light)
			light = tl;
	}
	return (light);
}

// double	get_light(t_cub *cub, t_dvec3 tar)
// {
// 	int		i;
// 	double	tl;
// 	double	light;
// 	double	d;

// 	i = -1;
// 	light = 0;
// 	d = dist((t_dvec3){cub->player.pos.x, cub->player.pos.z, 0}, tar);
// 	if (d < LIGHT_RANGE + 20)
// 		light = compute_light(d);
// 	while (++i < cub->sprite_count)
// 	{
// 		if (!cub->sprites[i].light)
// 			continue ;
// 		d = dist(cub->sprites[i].pos, tar);
// 		if (d >= pow(LIGHT_RANGE, 2))
// 			continue ;
// 		tl = compute_light(d);
// 		if (tl > light)
// 			light = tl;
// 	}
// 	return (light);
// }
