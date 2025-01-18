/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:43:37 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/16 18:40:26 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (next);
}

	// if (size < 0 || size > SH * 2)
	// 	size = SH * 2;

void	init_drawing_vars(t_cub *cub, t_sprite s, double d, t_sdrawing *dr)
{
	dr->size = SH / d;
	dr->col = 0x0;
	dr->ltc = (t_vec3){-1, -1, -1};
	dr->sp.x = s.scr.x - dr->size / 2 + 1;
	dr->light = 1.5;
	if (!s.light)
		dr->light = get_light(cub, s.pos);
	if (dr->sp.x < 0)
		dr->sp.x = -1;
}

void	draw_sprite(t_cub *cub, t_sprite sprite, double d, t_vec3 scr)
{
	t_sdrawing	dr;

	init_drawing_vars(cub, sprite, d, &dr);
	while (++dr.sp.x < scr.x + dr.size / 2 && dr.sp.x < SW)
	{
		if (cub->z_buffer[dr.sp.x] < d)
			continue ;
		dr.sp.y = scr.y - (dr.size / 2 + 1);
		if (dr.sp.y < 0)
			dr.sp.y = -1;
		while (++dr.sp.y < scr.y + dr.size / 2 && dr.sp.y < SH)
		{
			dr.texcoord.x = (int)(sprite.tex.width * ((dr.sp.x
							- (scr.x - dr.size / 2)) / (double)dr.size));
			dr.texcoord.y = (int)(sprite.tex.width * ((dr.sp.y
							- (scr.y - dr.size / 2)) / (double)dr.size));
			dr.texcoord.y += sprite.tex.width
				* ((int)(cub->info.last_frame / 125) % 4);
			get_sprite_color(sprite.tex, &dr);
			pixel_put(&cub->image, dr.sp.x + cub->headbob.x,
				dr.sp.y + cub->headbob.y, dr.col);
		}
	}
}

	/*
	for each sprite
	draw sprite if sprite dist < cub->z_buffer[x]
	*/
void	draw_sprites(t_cub *cub)
{
	t_sprite	*s;
	t_dvec3		diff;
	t_dvec3		transform;
	t_camera	cam;
	double		inv;

	cam.focal = 1.0;
	cam.plane = (t_dvec3){cos(cub->player.rot - M_PI / 2.0) * cam.focal,
		sin(cub->player.rot - M_PI / 2.0) * cam.focal, 0};
	inv = 1.0 / (cam.plane.x * sin(cub->player.rot)
			- cam.plane.y * cos(cub->player.rot));
	s = get_next_sprite(cub, NULL);
	while (s)
	{
		diff.x = (s->pos.x - cub->player.pos.x);
		diff.y = (s->pos.y - cub->player.pos.z);
		transform.x = inv * (sin(cub->player.rot) * diff.x
				- cos(cub->player.rot) * diff.y);
		transform.y = inv * (-cam.plane.y * diff.x + cam.plane.x * diff.y);
		s->scr.x = (int)((SW / 2) * (1 - transform.x / transform.y));
		s->scr.y = SH / 2;
		if (!(transform.y < 0.05 || s->scr.x < 0 || s->scr.x > SW))
			draw_sprite(cub, *s, transform.y, s->scr);
		s = get_next_sprite(cub, s);
	}
}
