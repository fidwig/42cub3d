/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:49:59 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/06 17:12:35 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

// void	pixel_put_force(t_image *image, int x, int y, unsigned int color)
// {
// 	char	*dst;

// 	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
// 		return ;
// 	dst = image->addr + (y * image->len + x * (image->bpp / 8));
// 	*(unsigned int *)dst = color;
// }

// t_image	create_notex(t_cub *cub)
// {
// 	t_image	notex;

// 	notex.img = mlx_new_image(cub->mlx, 2, 2);
// 	notex.width = 2;
// 	notex.height = 2;
// 	notex.addr = mlx_get_data_addr(notex.img, &notex.bpp, &notex.len,
// 		&notex.endian);
// 	// pixel_put(&notex, 0, 0, BLACK);
// 	pixel_put(&notex, 0, 1, 0xFF77FF);
// 	pixel_put(&notex, 1, 0, 0xFF77FF);
// 	// pixel_put(&notex, 1, 1, BLACK);
// 	return (notex);
// }

// t_uicol	halve(t_uicol a)
// {
// 	return (a >> 1 & 0x7f7f7f7f);
// }

// t_uicol	blend_colors(t_uicol b, t_uicol c)
// {
// 	// t_trgb	base;
// 	// t_trgb	rgb;
// 	// float	blend;
// 	// t_trgb	result;

// 	if (((c >> 24) & 0xFF) == 0xFF)
// 		return (b);
// 	else if (((c >> 24) & 0xFF) == 0x00)
// 		return (c);
// 	c = halve(c);
// 	b = halve(b);
// 	return (c + b);
// 	// base = utorgb(b);
// 	// rgb = utorgb(c);
// 	// blend = rgb.t / 255.0;
// 	// result.r = (unsigned char)((blend) * (float) base.r +
		// (1.0 - blend) * (float) rgb.r);
// 	// result.g = (unsigned char)((blend) * (float) base.g +
		// (1.0 - blend) * (float) rgb.g);
// 	// result.b = (unsigned char)((blend) * (float) base.b +
		// (1.0 - blend) * (float) rgb.b);
// 	// result.t = 0;
// 	// return (rgbtou(result));
// }

// void	set_transparency(t_image *i, unsigned char t)
// {
// 	int		x;
// 	int		y;
// 	t_trgb	rgb;

// 	x = 0;
// 	while (x < i->width)
// 	{
// 		y = 0;
// 		while (y < i->height)
// 		{
// 			rgb = utorgb(pixel_get(*i, x, y));
// 			rgb.t = t;
// 			pixel_put_force(i, x, y, rgbtou(rgb));
// 			printf("color: %x\n", pixel_get(*i, x, y));
// 			y++;
// 		}
// 		x++;
// 	}
// }
