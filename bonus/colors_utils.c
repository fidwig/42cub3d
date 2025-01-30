/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:57:33 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/30 14:06:58 by bazaluga         ###   ########.fr       */
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
	tint = utorgb(LIGHT_TINT);
	rgb.r = clamp(((rgb.r * tint.r) / 255) * light, 0, 255);
	rgb.g = clamp(((rgb.g * tint.g) / 255) * light, 0, 255);
	rgb.b = clamp(((rgb.b * tint.b) / 255) * light, 0, 255);
	return (rgbtou(rgb));
}

double	clamp(double n, double mini, double maxi)
{
	if (n < mini)
		n = mini;
	if (n > maxi)
		n = maxi;
	return (n);
}
