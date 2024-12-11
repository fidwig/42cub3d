/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:06:47 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/11 20:06:39 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	render_sky(t_cub *cub)
{
	t_image	tex;
	int		offset;
	int		x;
	int		y;
	t_vec3	texcoord;
	int		sky_height;
	int		visible_w;
	double	distortion;

	tex = cub->map.sky_tex;
	offset = tex.width * ((cub->player.rot) / (2 * M_PI));
	sky_height = SH / 2;
	visible_w = tex.width * 0.3;
	y = sky_height;
	while (y >= 0)
	{
		x = 0;
		while (x < SW)
		{
			distortion = (pow(((double) x / SW) - 0.5, 2)) * 2.0 + 1;
			// printf("%f\n", distortion);
			texcoord.x = ((double) x / SW) * (double)(visible_w) + offset;
			if (texcoord.x > tex.width)
				texcoord.x -= tex.width;
			texcoord.y = ((double)(sky_height - (y / distortion)) / sky_height) * (double) tex.height;
			pixel_put(&cub->image, x, sky_height - y, pixel_get(tex, texcoord.x, texcoord.y));
			x++;
		}
		y--;
	}
}
