/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:49:59 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/19 22:50:04 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	clear_image(t_image *image, t_uicol color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < SW)
	{
		j = 0;
		while (j < SH)
		{
			pixel_put(image, i, j, color);
			j++;
		}
		i++;
	}
}

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

void	pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > SW || y < 0 || y > SH)
		return ;
	dst = image->addr + (y * image->linelen + x * (image->bitdepth / 8));
	*(unsigned int *)dst = color;
}
