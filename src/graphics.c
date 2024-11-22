/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:32:29 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/21 23:09:53 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

void	draw_column(t_cub *cub, int x, int h, t_ray ray)
{
	int		j;
	t_trgb	col;
	t_image	tex;
	t_vec3	texcoord;
	double	light;

	if (h < 0)
		h = SH;
	light = pow((1.0 - (ray.length / 18)), 2);
	tex = get_tex(cub, ray.info.facing);
	texcoord.x = (int)(ray.info.x_wall * tex.width);
	if (ray.info.facing == EAST || ray.info.facing == SOUTH)
		texcoord.x = tex.width - texcoord.x - 1;
	texcoord.y = -1;
	j = SH / 2 - h / 2;
	while (++j < (SH / 2 + h / 2))
	{
		if (j > SH || j < 0)
			continue ;
		texcoord.z = (int)(tex.height * ((SH / 2 + h / 2 - j) % h) / h);
		if (texcoord.y != texcoord.z)
		{
			texcoord.y = texcoord.z;
			col = utorgb(pixel_get(tex, texcoord.x, texcoord.y));
			col.r = clamp(col.r * light, 0, 255);
			col.g = clamp(col.g * light, 0, 255);
			col.b = clamp(col.b * light, 0, 255);
		}
		pixel_put(&cub->image, x, j, rgbtou(col));
	}
}
