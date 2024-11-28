/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:49:59 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/04 19:00:03 by jsommet          ###   ########.fr       */
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

void	pixel_put_force(t_image *image, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	dst = image->addr + (y * image->len + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

void	pixel_put(t_image *image, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	if (((color >> 24) & 0xFF) == 0xFF)
		return ;
	dst = image->addr + (y * image->len + x * (image->bpp / 8));
	*(unsigned int *)dst = color;//blend_colors(*(unsigned int *)dst, color);
}

unsigned int	pixel_get(t_image image, int x, int y)
{
	char	*dst;

	if (x < 0 || x > image.width || y < 0 || y > image.height)
		return (0x0);
	dst = image.addr + (y * image.len + x * (image.bpp / 8));
	return (*(unsigned int *)dst);
}

t_image	create_notex(t_cub *cub)
{
	t_image	notex;

	notex.img = mlx_new_image(cub->mlx, 2, 2);
	notex.width = 2;
	notex.height = 2;
	notex.addr = mlx_get_data_addr(notex.img, &notex.bpp, &notex.len, &notex.endian);
	// pixel_put(&notex, 0, 0, BLACK);
	pixel_put(&notex, 0, 1, 0xFF77FF);
	pixel_put(&notex, 1, 0, 0xFF77FF);
	// pixel_put(&notex, 1, 1, BLACK);
	return (notex);
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

t_uicol	blend_colors(t_uicol b, t_uicol c)
{
	t_trgb	base;
	t_trgb	rgb;
	float	blend;
	t_trgb	result;

	base = utorgb(b);
	rgb = utorgb(c);
	if (((c >> 24) & 0xFF) == 0xFF)
		return (b);
	else if (((c >> 24) & 0xFF) == 0x00)
		return (c);
	blend = rgb.t / 255.0;
	result.r = (unsigned char)((blend) * (float) base.r + (1.0 - blend) * (float) rgb.r);
	result.g = (unsigned char)((blend) * (float) base.g + (1.0 - blend) * (float) rgb.g);
	result.b = (unsigned char)((blend) * (float) base.b + (1.0 - blend) * (float) rgb.b);
	result.t = 0;
	return (rgbtou(result));
}

void	set_transparency(t_image *i, unsigned char t)
{
	int		x;
	int		y;
	t_trgb	rgb;

	x = 0;
	while (x < i->width)
	{
		y = 0;
		while (y < i->height)
		{
			rgb = utorgb(pixel_get(*i, x, y));
			rgb.t = t;
			pixel_put_force(i, x, y, rgbtou(rgb));
			printf("color: %x\n", pixel_get(*i, x, y));
			y++;
		}
		x++;
	}
}
