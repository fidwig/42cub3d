/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:57:33 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/06 16:58:32 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

t_trgb	utorgb(unsigned int color)
{
	t_trgb	trgb;

	trgb.t = (color >> 24) & 0xFF;
	trgb.r = (color >> 16) & 0xFF;
	trgb.g = (color >> 8) & 0xFF;
	trgb.b = color & 0xFF;
	return (trgb);
}

unsigned int	rgbtou(t_trgb trgb)
{
	unsigned int	color;

	color = (trgb.t << 24 | trgb.r << 16 | trgb.g << 8 | trgb.b);
	return (color);
}

t_uicol	dim_color(t_uicol col, double light)
{
	t_trgb	rgb;

	rgb = utorgb(col);
	rgb.r = clamp(rgb.r * light, 0, 255);
	rgb.g = clamp(rgb.g * light, 0, 255);
	rgb.b = clamp(rgb.b * light, 0, 255);
	return (rgbtou(rgb));
}
