/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:43:37 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/11 17:09:58 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

double	dist(t_dvec3 a, t_dvec3 b)
{
	return (sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0) + pow(a.z - b.z, 2.0)));
}

void	draw_sprites(t_cub *cub)
{
	/*
	for each sprite
	draw sprite if sprite dist < cub->z_buffer[x]
	*/
	(void) cub;
	t_dvec3	spos = (t_dvec3) {5, 5, 0};
	double	d = dist(spos, (t_dvec3){cub->player.pos.x, cub->player.pos.z, 0});

	t_dvec3	diff;
	diff.x = cub->player.pos.x - spos.x;
	diff.y = cub->player.pos.z - spos.y;
	double	dngl = atan2(diff.y, diff.x);
	// wrap_angle(dngl);
	double	x_cam = (dngl - wrap_angle(cub->player.rot - deg2rad(FOV / 2))) / deg2rad(FOV);
	draw_square(&cub->image, (t_vec3) {(int)(x_cam * (double)SW), SH / 2, 0}, SH / d, 0x0CCAA8);
}