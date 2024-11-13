/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:49:59 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/13 00:57:33 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_rgb	utorgb(unsigned int color)
{
	t_rgb	rgb;

	rgb.t = (color >> 24) & 0xFF;
	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	return (rgb);
}

unsigned int	rgbtou(t_rgb rgb)
{
	unsigned int	color;

	color = (rgb.t << 24 | rgb.r << 16 | rgb.g << 8 | rgb.b);
	return (color);
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > S_WIDTH || y < 0 || y > S_HEIGHT)
		return ;
	dst = data->addr + (y * data->linelen + x * (data->bitdepth / 8));
	*(unsigned int *)dst = color;
}
