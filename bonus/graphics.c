/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:32:29 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/13 20:02:54 by jsommet          ###   ########.fr       */
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

t_image	get_wall_tex(t_cub *cub, t_dir facing)
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
	// return (cub->notex);

void	draw_layer(t_cub *cub, int x, int h, t_hit	info)
{
	int		j;
	t_image	tex;
	t_vec3	texcoord;
	double	light;
	t_uicol	col;

	light = cub->y_dist_lookup[(int)clamp((SH + h) / 2, 0, SH - 1)][1];
	tex = get_tex(cub, info.type, info.facing);
	texcoord.x = (int)(info.x_wall * tex.width);
	if (info.facing == EAST || info.facing == SOUTH)
		texcoord.x = tex.width - texcoord.x - 1;
	texcoord.z = -1;
	j = SH / 2 - h / 2 + 1;

	/*FC TEST*/
	t_fcdat fc;
	fc.info = info;
	init_fcdat(&fc);
	fc.w = cub->y_dist_lookup[(int)clamp((SH + h) / 2, 0, SH - 1)][0] / fc.info.dist;
	fc.cfloor.x = fc.w * fc.sfloor.x + (1.0 - fc.w) * cub->player.pos.x;
	fc.cfloor.y = fc.w * fc.sfloor.y + (1.0 - fc.w) * cub->player.pos.z;
	/*FC TEST*/
	
	if (j < 0)
		j = -1;
	while (++j < (SH / 2 + h / 2))
	{
		if (j > SH)
			break ;
		texcoord.y = (int)(tex.height * ((j - (SH / 2 - h / 2)) % h) / h);

		/*FC TEST*/
		double d = dist(fc.cfloor, (t_dvec3){3.2, 4.5, 0});
		d = sqrt(pow(d, 2) + pow(1 - (double)(j - (SH / 2 - h / 2)) / h, 2));
		double light2 = LIGHT_STRENGTH / (0.3 + d);
		if(light2 > light)
			light = light2;
		/*FC TEST*/

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
		if (ray.info[i].type == 'O' && (ray.info[i].x_wall < 0.125 || ray.info[i].x_wall > 0.875))
			cub->z_buffer[x] = ray.info[i].dist;
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
