/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:14:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/13 18:24:03 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	floorcasting(t_cub *cub, t_ray ray, int x)
{
	t_image tex;
	t_vec3	texcoord;
	int		y;
	t_hit	info;
	t_dvec3	wall_floor;
	t_dvec3 current_floor;
	double	weight;
	double	h;

	tex = cub->map.tex_floor;
	info = ray.info[ray.hit_count - 1];
	if (info.facing == EAST)
	{
		wall_floor.x = info.pos.x;
		wall_floor.y = info.pos.y + info.x_wall;
	}
	else if (info.facing == WEST)
	{
		wall_floor.x = info.pos.x + 1.0;
		wall_floor.y = info.pos.y + info.x_wall;
	}
	else if (info.facing == NORTH)
	{
		wall_floor.x = info.pos.x + info.x_wall;
		wall_floor.y = info.pos.y;
	}
	else
	{
		wall_floor.x = info.pos.x + info.x_wall;
		wall_floor.y = info.pos.y + 1.0;
	}
	h = SH / (info.dist * 1.0);
	if (h < 0)
		h = SH;
	y = SH / 2 + h / 2 - 1;
	while (y < SH)
	{
		weight = cub->y_dist_lookup[y][0] / info.dist;
		current_floor.x = weight * wall_floor.x + (1.0 - weight) * ray.origin.x;
		current_floor.y = weight * wall_floor.y + (1.0 - weight) * ray.origin.z;
		texcoord.x = (int)(current_floor.x * tex.width) % tex.width;
		texcoord.y = (int)(current_floor.y * tex.height) % tex.height;
		pixel_put(&cub->image, x, y,
			dim_color(pixel_get(tex, texcoord.x, texcoord.y),
				cub->y_dist_lookup[y][1]));
		y++;
	}
}
