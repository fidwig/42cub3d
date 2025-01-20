/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:06:47 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/20 17:50:11 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

//texcoord.z is the texcoord offset because of the stupid norm
//  - dotp(cub->player.upos, a2dv(cub->player.yaw + M_PI / 2)) * 5.0

void	render_sky(t_cub *cub)
{
	t_image	tex;
	t_vec3	scr;
	t_vec3	texcoord;
	int		visible_w;
	double	distortion;

	tex = cub->map.sky_tex;
	texcoord.z = (double)tex.width * ((cub->player.yaw) / (2 * M_PI))
		- dotp(a2dv(cub->player.yaw + M_PI / 2), cub->player.upos) * 10.0;
	visible_w = tex.width * 0.3;
	scr.y = SKY_HEIGHT + 1;
	while (--scr.y >= 0)
	{
		scr.x = -1;
		while (++scr.x < SW)
		{
			distortion = (pow(((double) scr.x / SW) - 0.5, 2)) * +2.0 + 1.0;
			texcoord.x = ((double)scr.x / SW) * visible_w + texcoord.z;
			if (texcoord.x > tex.width)
				texcoord.x -= tex.width;
			texcoord.y = (1 - scr.y / (distortion * SKY_HEIGHT)) * tex.height;
			pixel_put(&cub->image, scr.x + cub->headbob.x, SKY_HEIGHT - scr.y
				+ cub->headbob.y, pixel_get(tex, texcoord.x, texcoord.y));
		}
	}
}
