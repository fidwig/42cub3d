/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:14:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/12 21:42:08 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	floorcasting(t_cub *cub, t_ray ray, int x)
{
	t_hit	info;
	t_dvec3	wall_floor;
	double	current_dist;
	double	h;
	int		y;
	t_dvec3 current_floor;
	t_vec3 texcoord;
	double weight;
	double light;
	t_image tex;

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
	y = SH / 2 + h / 2 - 2;
	while (y < SH)
	{
		current_dist = SH / (2.0 * y - SH);
		weight = current_dist / info.dist;
		light = pow((1.0 - (current_dist / 18)), 2);
		current_floor.x = weight * wall_floor.x + (1.0 - weight) * ray.origin.x;
		current_floor.y = weight * wall_floor.y + (1.0 - weight) * ray.origin.z;
		texcoord.x = (int)(current_floor.x * tex.width) % tex.width;
		texcoord.y = (int)(current_floor.y * tex.height) % tex.height;
		pixel_put(&cub->image, x, y,
			dim_color(pixel_get(tex, texcoord.x, texcoord.y), light));
		y++;
	}
}
		// pixel_put(&cub->image, x, SH - y, dim_color(pixel_get(tex, texcoord.x, texcoord.y), light));
