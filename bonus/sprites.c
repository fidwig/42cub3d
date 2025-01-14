/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:43:37 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/14 17:15:43 by jsommet          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub_bonus.h"

double	dist(t_dvec3 a, t_dvec3 b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y)
			* (a.y - b.y) + (a.z - b.z) * (a.z - b.z)));
}

t_sprite	*get_next_sprite(t_cub *cub, t_sprite *last)
{
	t_sprite	*next;
	double		d;
	double		dn;
	double		dc;
	int			i;

	d = 1e4;
	if (last)
		d = dist((t_dvec3){cub->player.pos.x, cub->player.pos.z, 0}, last->pos);
	next = NULL;
	dn = 0;
	i = -1;
	while (++i < cub->sprite_count)
	{
		dc = dist((t_dvec3){cub->player.pos.x, cub->player.pos.z, 0},
				cub->sprites[i].pos);
		if (dc < d && (dc > dn))
		{
			next = &cub->sprites[i];
			dn = dc;
		}
	}
	dprintf(2, "\n");
	return (next);
}

	// if (size < 0 || size > SH * 2)
	// 	size = SH * 2;
void	draw_sprite(t_cub *cub, t_sprite sprite, double d, t_vec3 screen_pos)
{
	t_vec3	sp;
	t_vec3	texcoord;
	double	light;
	int		size;

	size = SH / d;
	sp.x = screen_pos.x - size / 2 + 1;
	light = 1.5;
	if (!sprite.light)
		light = get_light(cub, sprite.pos,
				cub->y_dist_lookup[(int)clamp(screen_pos.x + size / 2, 0, 255)][1]);
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
			texcoord.x = (int)(sprite.tex.width * ((sp.x - (screen_pos.x - size / 2)) / (double)size));
			texcoord.y = (int)(sprite.tex.width * ((sp.y - (screen_pos.y - size / 2)) / (double)size));
			texcoord.y += sprite.tex.width * ((int)(cub->info.last_frame / 125) % 4);
			pixel_put(&cub->image, sp.x + cub->headbob.x, sp.y + cub->headbob.y,
				dim_color(pixel_get(sprite.tex, texcoord.x, texcoord.y), 1.5));
		}
	}
}

	/*
	for each sprite
	draw sprite if sprite dist < cub->z_buffer[x]
	*/
void	draw_sprites(t_cub *cub)
{
	t_sprite *sprite;
	t_dvec3	transform;
	t_dvec3	diff;
	t_vec3	screen_pos;
	t_camera cam;
	double	inv_det;

	cam.focal = 1.0;
	cam.plane = (t_dvec3){cos(cub->player.rot - M_PI / 2.0) * cam.focal,
		sin(cub->player.rot - M_PI / 2.0) * cam.focal, 0};
	inv_det = 1.0 / (cam.plane.x * sin(cub->player.rot) - cam.plane.y * cos(cub->player.rot));
	sprite = get_next_sprite(cub, NULL);
	while (sprite)
	{
		diff.x = (sprite->pos.x - cub->player.pos.x);
		diff.y = (sprite->pos.y - cub->player.pos.z);
		transform.x = inv_det * (sin(cub->player.rot) * diff.x - cos(cub->player.rot) * diff.y);
		transform.y = inv_det * (-cam.plane.y * diff.x + cam.plane.x * diff.y);
		screen_pos.x = (int)((SW / 2) * (1 - transform.x / transform.y));
		screen_pos.y = SH / 2;
		if (!(transform.y < 0.05 || screen_pos.x < 0 || screen_pos.x > SW))
			draw_sprite(cub, *sprite, transform.y, screen_pos);
		sprite = get_next_sprite(cub, sprite);
	}
}
// double	dngl = wrap_angle(atan2(diff.y, diff.x) - cub->player.rot);
// if (dngl > M_PI)
// 	dngl -= 2 * M_PI;

// double	x_cam = (dngl + deg2rad(FOV / 2)) / deg2rad(FOV);
// if (x_cam < -0.2 || x_cam > 1.2)
// 	return ;rd.y));