/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:39:53 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/19 16:46:01 by jsommet          ###   ########.fr       */
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

double	deg2rad(int deg)
{
	return ((deg / 180.0) * M_PI);
}
