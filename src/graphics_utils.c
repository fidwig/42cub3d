/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:49:59 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/22 00:47:26 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	clear_image(t_image *image, t_uicol color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < image->width)
	{
		j = 0;
		while (j < image->height)
		{
			pixel_put(image, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_image(t_image *dest, t_image *src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < src->width)
	{
		j = 0;
		while (j < src->height)
		{
			pixel_put(dest, x + i, y + j, pixel_get(*src, i, j));
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

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	dst = image->addr + (y * image->len + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	pixel_get(t_image image, int x, int y)
{
	char	*dst;

	if (x < 0 || x > image.width || y < 0 || y > image.height)
		return (0x0);
	dst = image.addr + (y * image.len + x * (image.bpp / 8));
	return (*(unsigned int *)dst);
}
