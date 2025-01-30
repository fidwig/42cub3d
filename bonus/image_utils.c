/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:56:18 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/30 13:55:55 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

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

void	clear_image_bicolor(t_image *image, t_uicol color1, t_uicol color2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < image->width)
	{
		j = -1;
		while (++j < image->height / 2)
			pixel_put(image, i, j, color1);
		while (++j < image->height)
			pixel_put(image, i, j, color2);
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

void	pixel_put(t_image *image, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	if (((color >> 24) & 0xFF) == 0xFF)
		return ;
	dst = image->addr + (y * image->len + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	pixel_get(t_image image, int x, int y)
{
	char	*dst;

	if (x >= image.width)
		x -= image.width;
	else if (x < 0)
		x += image.width;
	if (y >= image.height)
		y -= image.height;
	else if (y < 0)
		y += image.height;
	dst = image.addr + (y * image.len + x * (image.bpp / 8));
	return (*(unsigned int *)dst);
}
