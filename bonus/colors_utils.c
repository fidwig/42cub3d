/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:57:33 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/11 20:35:30 by jsommet          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	tint = utorgb(LIGHT_TINT);
	rgb.r = clamp(((rgb.r * tint.r) / 255) * light, 0, 255);
	rgb.g = clamp(((rgb.g * tint.g) / 255) * light, 0, 255);
	rgb.b = clamp(((rgb.b * tint.b) / 255) * light, 0, 255);
	return (rgbtou(rgb));
}
// rgb.r = clamp(rgb.r * light * 0.7 + tint.r * light * 0.3 - rtint.r * light * 0.1, 0, 255);
// rgb.g = clamp(rgb.g * light * 0.7 + tint.g * light * 0.3 - rtint.g * light * 0.1, 0, 255);
// rgb.b = clamp(rgb.b * light * 0.7 + tint.b * light * 0.3 - rtint.b * light * 0.1, 0, 255);

t_uicol	apply_light(t_uicol col, t_uicol tint, double light)
{
	t_trgb	rgb;
	t_trgb	rgb_tint;

	if (light == 0.0)
		return (0x0);
	rgb = utorgb(col);
	rgb_tint = utorgb(tint);
	rgb.r = clamp(((rgb.r * rgb_tint.r) / 255) * light, 0, 255);
	rgb.g = clamp(((rgb.g * rgb_tint.g) / 255) * light, 0, 255);
	rgb.b = clamp(((rgb.b * rgb_tint.b) / 255) * light, 0, 255);
	return (rgbtou(rgb));
}
