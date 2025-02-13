/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:32:29 by jsommet           #+#    #+#             */
/*   Updated: 2025/02/01 21:40:29 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

t_image	get_wall_tex(t_cub *cub, t_dir facing)
{
	if (facing == NORTH)
		return (cub->map.nor_tex);
	else if (facing == WEST)
		return (cub->map.eas_tex);
	else if (facing == SOUTH)
		return (cub->map.sou_tex);
	else
		return (cub->map.wes_tex);
}

t_image	get_tex(t_cub *cub, char type, t_dir facing)
{
	if (type == '1')
		return (get_wall_tex(cub, facing));
	else if (type == 'D')
		return (cub->map.door_tex);
	else if (type == 'O')
		return (cub->map.opendoor_tex);
	else
		return (get_wall_tex(cub, facing));
}

double	get_fc_light(t_cub *cub, t_hit info, int h)
{
	t_fcdat	fc;

	fc.info = info;
	init_fcdat(cub, &fc, (SH + h) / 2);
	return (fc.light);
}

void	draw_layer(t_cub *cub, int x, int h, t_hit	info)
{
	int		j;
	t_image	tex;
	t_vec3	texcoord;
	double	light;
	t_uicol	col;

	light = get_fc_light(cub, info, h);
	tex = get_tex(cub, info.type, info.facing);
	texcoord.x = (int)(info.x_wall * tex.width);
	if (info.facing == EAST || info.facing == SOUTH)
		texcoord.x = tex.width - texcoord.x - 1;
	col = 0x0;
	texcoord.z = -1;
	j = SH / 2 - h / 2 + 1;
	if (j < 0)
		j = -1;
	while (++j < (SH / 2 + h / 2) && j <= SH)
	{
		texcoord.y = (int)(tex.height * ((j - (SH / 2 - h / 2)) % h) / h);
		if (texcoord.y != texcoord.z)
			col = dim_color(pixel_get(tex, texcoord.x, texcoord.y), light);
		texcoord.z = texcoord.y;
		pixel_put(&cub->image, x + cub->headbob.x, j + cub->headbob.y, col);
	}
}

void	draw_column_layers(t_cub *cub, int x, t_ray ray, double focal)
{
	int	h;
	int	i;

	cub->z_buffer[x] = ray.info[ray.hits - 1].dist;
	i = ray.hits;
	while (--i >= 0)
	{
		if (ray.info[i].type == 'O' && (ray.info[i].x_wall < 0.125
				|| ray.info[i].x_wall > 0.875))
			cub->z_buffer[x] = ray.info[i].dist;
		h = (int)(SH / (ray.info[i].dist * focal));
		if (h < 0)
			h = SH;
		draw_layer(cub, x, h, ray.info[i]);
	}
}
