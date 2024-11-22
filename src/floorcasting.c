/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:14:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/22 01:43:07 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	floorcasting(t_cub *cub)
{
	int			y;
	int			x;
	t_camera	cam;
	t_image		tex;
	t_trgb		col;

	tex = cub->map.tex_nor;
	cam.focal = tan(deg2rad(FOV / 2.0));
	cam.plane = (t_dvec3){cos(cub->player.rot - M_PI / 2.0) * cam.focal,
		sin(cub->player.rot - M_PI / 2.0) * cam.focal, 0};
	y = -1;
	while (++y < SH / 2)
	{
		t_dvec3	raydir0;
		t_dvec3	raydir1;
		t_dvec3 floorstep;
		t_dvec3 floor;
		t_vec3 texcoord;
		t_vec3 cell;
		// int p = SH / 2 - y;
		// float posY = SH / 2;
		float rowdist = (SH / 2.0) / (y - SH / 2.0);
		// double	light = pow((1.0 - (rowdist / 18)), 2);

		raydir0.x = cos(cub->player.rot + M_PI) - cam.plane.x;
		raydir0.y = sin(cub->player.rot + M_PI) - cam.plane.y;
		raydir1.x = cos(cub->player.rot + M_PI) + cam.plane.x;
		raydir1.y = sin(cub->player.rot + M_PI) + cam.plane.y;
		floorstep.x = rowdist * (raydir1.x - raydir0.x) / (double)SW;
		floorstep.y = rowdist * (raydir1.y - raydir0.y) / (double)SW;
		floor.x = cub->player.pos.x + rowdist * raydir0.x;
		floor.y = cub->player.pos.z + rowdist * raydir0.y;
		x = -1;
		while (++x < SW)
		{
			// double	camera_x = 2.0 * (1 - x / ((double)SW)) - 1.0;
			// t_dvec3	ray_dir = (t_dvec3){cos(cub->player.rot + M_PI) + cam.plane.x * camera_x,
			// 	sin(cub->player.rot + M_PI) + cam.plane.y * camera_x, 0};
			// floorstep.x = rowdist * (ray_dir.x - raydir0.x) / (double)SW;
			// floorstep.y = rowdist * (ray_dir.y - raydir0.y) / (double)SW;
			cell.x = (int) floor.x;
			cell.y = (int) floor.y;
			texcoord.x = (int)(tex.width * (floor.x - cell.x)) & (tex.width - 1);
			texcoord.y = (int)(tex.height * (floor.y - cell.y)) & (tex.height - 1);
			floor.x += floorstep.x;
			floor.y += floorstep.y;
			col = utorgb(pixel_get(tex, texcoord.x, texcoord.y));
			// col.r = clamp(col.r * light, 0, 255);
			// col.g = clamp(col.g * light, 0, 255);
			// col.b = clamp(col.b * light, 0, 255);
			// if ((cell.x + cell.y) % 2)
			// 	col = utorgb(0xFFAA55);
			// else
			// 	col = utorgb(0x55AAFF);
			pixel_put(&cub->image, x, SH - y - 10, rgbtou(col));
			pixel_put(&cub->image, x, y + 10, rgbtou(col));
		}
	}
}
