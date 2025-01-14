/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:14:54 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/14 18:41:17 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	init_fcdat(t_cub *cub, t_fcdat *fc, int y)
{
	if (fc->info.facing == EAST)
	{
		fc->sfloor.x = fc->info.pos.x;
		fc->sfloor.y = fc->info.pos.y + fc->info.x_wall;
	}
	else if (fc->info.facing == WEST)
	{
		fc->sfloor.x = fc->info.pos.x + 1.0;
		fc->sfloor.y = fc->info.pos.y + fc->info.x_wall;
	}
	else if (fc->info.facing == NORTH)
	{
		fc->sfloor.x = fc->info.pos.x + fc->info.x_wall;
		fc->sfloor.y = fc->info.pos.y;
	}
	else
	{
		fc->sfloor.x = fc->info.pos.x + fc->info.x_wall;
		fc->sfloor.y = fc->info.pos.y + 1.0;
	}
	if (y >= SH)
		y = SH - 1;
	fc->light = get_light(cub, fc->sfloor, cub->y_dist_lookup[y][1]);
}

void	floorcasting(t_cub *cub, t_ray ray, int x)
{
	t_image	tex;
	t_vec3	texcoord;
	int		y;
	t_fcdat	fc;
	double	h;

	tex = cub->map.tex_floor;
	fc.info = ray.info[ray.hits - 1];
	h = clamp(SH / (fc.info.dist * 1.0), 0, SH);
	y = SH / 2 + h / 2 - 1;
	init_fcdat(cub, &fc, y);
	while (++y < SH)
	{
		fc.w = cub->y_dist_lookup[y][0] / fc.info.dist;
		fc.cfloor.x = fc.w * fc.sfloor.x + (1.0 - fc.w) * ray.origin.x;
		fc.cfloor.y = fc.w * fc.sfloor.y + (1.0 - fc.w) * ray.origin.z;
		texcoord.x = (int)(fc.cfloor.x * tex.width) % tex.width;
		texcoord.y = (int)(fc.cfloor.y * tex.height) % tex.height;
		if ((x + y) % 2)
			fc.light = get_light(cub, fc.cfloor, cub->y_dist_lookup[y][1]);
		pixel_put(&cub->image, x + cub->headbob.x, y + cub->headbob.y,
			dim_color(pixel_get(tex, texcoord.x, texcoord.y),
				fc.light));
	}
}
