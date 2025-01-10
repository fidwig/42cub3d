/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:57:33 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/12 21:04:28 by jsommet          ###   ########.fr       */
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

t_trgb	invert_rgb(t_trgb col)
{
	col.r = 255 - col.r;
	col.g = 255 - col.g;
	col.b = 255 - col.b;
	return (col);
}	

t_uicol	dim_color(t_uicol col, double light)
{
	t_trgb	rgb;
	t_trgb	tint;

	if (light == 0.0)
		return (0x0);
	rgb = utorgb(col);
	tint = invert_rgb(utorgb(LIGHT_TINT));
	rgb.r = clamp(rgb.r * light - tint.r * light * 0.1, 0, 255);
	rgb.b = clamp(rgb.b * light - tint.b * light * 0.1, 0, 255);
	rgb.g = clamp(rgb.g * light - tint.g * light * 0.1, 0, 255);
	return (rgbtou(rgb));
}

t_uicol	apply_light(t_uicol col, t_uicol tint, double light)
{
	t_trgb	rgb;
	t_trgb	rtint;

	if (light == 0.0)
		return (0x0);
	rgb = utorgb(col);
	rtint = invert_rgb(utorgb(tint));
	rgb.r = clamp(rgb.r * light - rtint.r * light, 0, 255);
	rgb.g = clamp(rgb.g * light - rtint.g * light, 0, 255);
	rgb.b = clamp(rgb.b * light - rtint.b * light, 0, 255);
	return (rgbtou(rgb));
}
