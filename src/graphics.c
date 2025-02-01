/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:32:29 by jsommet           #+#    #+#             */
/*   Updated: 2025/02/01 21:38:03 by jsommet          ###   ########.fr       */
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
	else if (facing == WEST)
		return (cub->map.tex_eas);
	else if (facing == SOUTH)
		return (cub->map.tex_sou);
	else
		return (cub->map.tex_wes);
}

void	draw_column(t_cub *cub, int x, int h, t_ray ray)
{
	int		j;
	t_uicol	col;
	t_image	tex;
	t_vec3	texcoord;

	if (h < 0)
		h = SH;
	tex = get_tex(cub, ray.info.facing);
	texcoord.x = (int)(ray.info.x_wall * tex.width);
	if (ray.info.facing == EAST || ray.info.facing == SOUTH)
		texcoord.x = tex.width - texcoord.x - 1;
	texcoord.z = -1;
	j = SH / 2 - h / 2;
	if (j < 0)
		j = -1;
	while (++j < (SH / 2 + h / 2) && j <= SH)
	{
		if (j < 0)
			continue ;
		texcoord.y = (int)(tex.height * ((j - (SH / 2 - h / 2)) % h) / h);
		if (texcoord.y != texcoord.z)
			col = pixel_get(tex, texcoord.x, texcoord.y);
		texcoord.z = texcoord.y;
		pixel_put(&cub->image, x, j, col);
	}
}
