/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:39:53 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/12 17:50:14 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

double	wrap_angle(double angle)
{
	if (angle >= 2.0 * M_PI)
		angle -= 2.0 * M_PI;
	else if (angle < 0)
		angle += 2.0 * M_PI;
	return (angle);
}

double	deg2rad(int deg)
{
	return ((deg / 180.0) * M_PI);
}

double	dotp(t_dvec3 a, t_dvec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_dvec3	a2dv(double angle)
{
	return ((t_dvec3){cos(angle), sin(angle), 0});
}
