/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:43:37 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/13 16:05:33 by jsommet          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub_bonus.h"

double	dist(t_dvec3 a, t_dvec3 b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y)
			* (a.y - b.y) + (a.z - b.z) * (a.z - b.z)));
}

t_sprite	*get_next_sprite(t_cub *cub)
{
	static t_sprite		*next;
	double				d;
	int					i;

	i = -1;
	if (next)
		d = next->dist;
	else
		d = 1e4;
	next = NULL;
	while (++i < cub->sprite_count)
	{
		if (cub->sprites[i].dist < d && (!next || cub->sprites[i].dist > next->dist))
			next = &cub->sprites[i];
	}
	return (next);
}

void	draw_sprite(t_cub *cub, t_image tex, double d, t_vec3 screen_pos)
{
	t_vec3	sp;
	t_vec3	texcoord;
	int		size;

	size = SH / d;
	sp.x = screen_pos.x - size / 2 + 1;
	if (sp.x < 0)
		sp.x = -1;
	while (++sp.x < screen_pos.x + size / 2 && sp.x < SW)
	{
		if (cub->z_buffer[sp.x] < d)
			continue ;
		sp.y = screen_pos.y - (size / 2 + 1);
		if (sp.y < 0)
			sp.y = -1;
		while (++sp.y < screen_pos.y + size / 2 && sp.y < SH)
		{
			texcoord.x = (int)(tex.width * ((sp.x - (screen_pos.x - size / 2)) / (double)size));
			texcoord.y = (int)(tex.width * ((sp.y - (screen_pos.y - size / 2)) / (double)size));
			texcoord.y += tex.width * ((int)(cub->info.last_frame / 125) % 4);
			pixel_put(&cub->image, sp.x + cub->headbob.x, sp.y + cub->headbob.y, dim_color(pixel_get(tex, texcoord.x, texcoord.y), 1.5 + 0*LIGHT_STRENGTH/(0.9 + d)));
		}
	}
}

	/*
	for each sprite
	draw sprite if sprite dist < cub->z_buffer[x]
	*/
void	draw_sprites(t_cub *cub)
{
	// t_sprite *sprite;
	t_dvec3	transform;
	t_dvec3	diff;
	t_vec3	screen_pos;
	t_camera cam;
	double	inv_det;

	cam.focal = 1.0;
	cam.plane = (t_dvec3){cos(cub->player.rot - M_PI / 2.0) * cam.focal,
		sin(cub->player.rot - M_PI / 2.0) * cam.focal, 0};
	inv_det = 1.0 / (cam.plane.x * sin(cub->player.rot) - cam.plane.y * cos(cub->player.rot));
	// sprite = get_next_sprite(cub);
	// while (sprite != NULL)
	int i = -1;
	while (++i < cub->sprite_count)
	{
		diff.x = (cub->sprites[i].pos.x - cub->player.pos.x);
		diff.y = (cub->sprites[i].pos.y - cub->player.pos.z);
		transform.x = inv_det * (sin(cub->player.rot) * diff.x - cos(cub->player.rot) * diff.y);
		transform.y = inv_det * (-cam.plane.y * diff.x + cam.plane.x * diff.y);
		if (transform.y < 0.05)
			continue ;
		screen_pos.x = (int)((SW / 2) * (1 - transform.x / transform.y));
		screen_pos.y = SH / 2;
		draw_sprite(cub, cub->sprites[i].tex, transform.y, screen_pos);
		// sprite = get_next_sprite(cub);
	}
}
// double	dngl = wrap_angle(atan2(diff.y, diff.x) - cub->player.rot);
// if (dngl > M_PI)
// 	dngl -= 2 * M_PI;

// double	x_cam = (dngl + deg2rad(FOV / 2)) / deg2rad(FOV);
// if (x_cam < -0.2 || x_cam > 1.2)
// 	return ;rd.y));