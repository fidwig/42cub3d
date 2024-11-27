/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:32:29 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/04 18:56:24 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

double	clamp(double n, double mini, double maxi)
{
	if (n < mini)
		n = mini;
	if (n > maxi)
		n = maxi;
	return (n);
}

t_image	get_tex(t_cub *cub, t_dir facing)
{
	if (facing == NORTH)
		return (cub->map.tex_nor);
	else if (facing == EAST)
		return (cub->map.tex_eas);
	else if (facing == SOUTH)
		return (cub->map.tex_sou);
	else
		return (cub->map.tex_wes);
}

void	draw_layer(t_cub *cub, int x, int h, t_hit	info)
{
	int		j;
	t_image	tex;
	t_vec3	texcoord;
	double	light;
	t_uicol	col;

	light = pow((1.0 - (info.dist / 18)), 2);
	if (info.type == 'D')
		tex = cub->map.door_tex;
	else if (info.type == 'O')
		tex = cub->map.opendoor_tex;
	else
		tex = get_tex(cub, info.facing);
	texcoord.x = (int)(info.x_wall * tex.width);
	if (info.facing == EAST || info.facing == SOUTH)
		texcoord.x = tex.width - texcoord.x - 1;
	texcoord.y = -1;
	j = SH / 2 - h / 2;
	if (j < 0)
		j = -1;
	// int	start = (SH / 2 - h / 2);
	while (++j < (SH / 2 + h / 2))
	{
		if (j > SH)
			break ;
		texcoord.z = (int)(tex.height * ((j - (SH / 2 - h / 2)) % h) / h);
		if (texcoord.y != texcoord.z)
		{
			texcoord.y = texcoord.z;
			col = dim_color(pixel_get(tex, texcoord.x, texcoord.y), light);
		}
		pixel_put(&cub->image, x, j, col);
	}
	if (info.type != 'T')
		return ;
	tex = cub->map.torch_tex;
	texcoord.x = (int)(info.x_wall * tex.height);
	if (info.facing == EAST || info.facing == SOUTH)
		texcoord.x = tex.height - texcoord.x - 1;
	texcoord.x += tex.height * ((cub->info.last_frame / (1000 / 12)) % 4);
	if (texcoord.x >= tex.width)
		texcoord.x -= tex.width;
	texcoord.y = -1;
	j = SH / 2 - h / 2;
	while (++j < (SH / 2 + h / 2))
	{
		if (j > SH)
			break ;
		texcoord.z = (int)(tex.height * ((j - (SH / 2 - h / 2)) % h) / h);
		if (texcoord.y != texcoord.z)
		{
			texcoord.y = texcoord.z;
			col = pixel_get(tex, texcoord.x, texcoord.y);//, light);
		}
		pixel_put(&cub->image, x, j, col);
	}
}

void	draw_column_layers(t_cub *cub, int x, t_ray ray, double focal)
{
	int	h;
	int	i;

	i = ray.hit_count;
	while (--i >= 0)
	{
		h = (int)(SH / (ray.info[i].dist * focal));
		if (h < 0)
			h = SH;
		draw_layer(cub, x, h, ray.info[i]);
	}
}

// void	draw_column(t_cub *cub, int x, int h, t_ray ray)
// {
// 	int		j;
// 	t_trgb	col;
// 	t_image	tex;
// 	t_vec3	texcoord;
// 	double	light;

// 	if (h < 0)
// 		h = SH;
// 	light = pow((1.0 - (ray.length / 18)), 2);
// 	tex = get_tex(cub, ray.info[0].facing);
// 	texcoord.x = (int)(ray.info[0].x_wall * tex.width);
// 	if (ray.info[0].facing == EAST || ray.info[0].facing == SOUTH)
// 		texcoord.x = tex.width - texcoord.x - 1;
// 	texcoord.y = -1;
// 	j = SH / 2 - h / 2;
// 	// j = SH / 2 - h / 2.5;
// 	while (++j < (SH / 2 + h / 2))
// 	{
// 		if (j > SH || j < 0)
// 			continue ;
// 		texcoord.z = (int)(tex.height * ((j - (SH / 2 - h / 2)) % h) / h);
// 		if (texcoord.y != texcoord.z)
// 		{
// 			texcoord.y = texcoord.z;
// 			col = utorgb(pixel_get(tex, texcoord.x, texcoord.y));
// 			col.r = clamp(col.r * light, 0, 255);
// 			col.g = clamp(col.g * light, 0, 255);
// 			col.b = clamp(col.b * light, 0, 255);
// 		}
// 		pixel_put(&cub->image, x, j, rgbtou(col));
// 	}
// 	// if (!is_prop(ray.info.type))
// 	// 	return ;
// 	// t_image prop_tex;
// 	// prop_tex = get_prop_tex(cub, ray.info.type);
// 	// j = SH / 2 - h / 2;
// 	// texcoord.x = (int)(ray.info.x_wall * tex.width);
// 	// if (ray.info.facing == EAST || ray.info.facing == SOUTH)
// 	// 	texcoord.x = tex.width - texcoord.x - 1;
// 	// texcoord.y = -1;
// 	// while (++j < (SH / 2 + h / 2))
// 	// {
// 	// 	if (j > SH || j < 0)
// 	// 		continue ;
// 	// 	texcoord.z = (int)(tex.height * ((SH / 2 + h / 2 - j) % h) / h);
// 	// 	if (texcoord.y != texcoord.z)
// 	// 	{
// 	// 		texcoord.y = texcoord.z;
// 	// 		col = utorgb(pixel_get(prop_tex, texcoord.x, texcoord.y));
// 	// 		col.r = clamp(col.r * light, 0, 255);
// 	// 		col.g = clamp(col.g * light, 0, 255);
// 	// 		col.b = clamp(col.b * light, 0, 255);
// 	// 	}
// 	// 	pixel_put(&cub->image, x, j, rgbtou(col));
// 	// }
// }
