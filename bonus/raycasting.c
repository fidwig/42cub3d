/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:37:31 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/13 19:33:12 by jsommet          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub_bonus.h"

void	dda_step(t_cast_data *cast, t_map map)
{
	if (cast->side_dist.x < cast->side_dist.y)
	{
		cast->side_dist.x += cast->delta.x;
		cast->mpos.x += cast->step.x;
		cast->flag = 0;
	}
	else
	{
		cast->side_dist.y += cast->delta.y;
		cast->mpos.y += cast->step.y;
		cast->flag = 1;
	}
	if (is_visible(map.raw[cast->mpos.y][cast->mpos.x]))
	{
		set_ray_info(cast->ray, *cast, &cast->ray.info[cast->ray.hits]);
		cast->ray.hits++;
		cast->hit = (!is_see_through(map.raw[cast->mpos.y][cast->mpos.x])
				|| cast->ray.hits >= RAY_DEPTH);
		if (!cast->hit && cast->ray.hits < RAY_DEPTH - 1)
		{
			add_ray_info(cast->ray, *cast, &cast->ray.info[cast->ray.hits]);
			cast->ray.hits++;
		}
	}
}

		// if (cast->flag)
		// 	cast->ray.dir.y *= -1;
		// else
		// 	cast->ray.dir.x *= -1;

void	dda(t_cast_data	*cast, t_map map)
{
	if (is_see_through(map.raw[cast->mpos.y][cast->mpos.x]))
	{
		cast->flag = (cast->side_dist.x >= cast->side_dist.y);
		cast->side_dist.x += cast->delta.x;
		cast->side_dist.y += cast->delta.y;
		set_ray_info(cast->ray, *cast, &cast->ray.info[cast->ray.hits++]);
		cast->side_dist.x -= cast->delta.x;
		cast->side_dist.y -= cast->delta.y;
	}
	while (!cast->hit)
		dda_step(cast, map);
}

t_ray	cast_ray(t_dvec3 origin, t_dvec3 dir, t_map map)
{
	t_cast_data	cast;

	cast = (t_cast_data){0};
	cast.map = map;
	cast.ray.dir = dir;
	cast.ray.origin = origin;
	cast.pos = (t_dvec3){origin.x, origin.z, 0};
	cast.mpos = (t_vec3){(int)origin.x, (int)origin.z, 0};
	cast_init(&cast);
	dda(&cast, map);
	return (cast.ray);
}

void	raycasting(t_cub *cub)
{
	int			x;
	t_ray		ray;
	t_dvec3		ray_dir;
	double		camera_x;
	t_camera	cam;

	cam.focal = 1.0;
	cam.plane = (t_dvec3){cos(cub->player.rot - M_PI / 2.0) * cam.focal,
		sin(cub->player.rot - M_PI / 2.0) * cam.focal, 0};
	x = -1;
	while (++x < SW)
	{
		camera_x = 2.0 * (1 - x / ((double)SW)) - cam.focal;
		ray_dir = (t_dvec3){cos(cub->player.rot) + cam.plane.x * camera_x,
			sin(cub->player.rot) + cam.plane.y * camera_x, 0};
		ray = cast_ray(cub->player.pos, ray_dir, cub->map);
		floorcasting(cub, ray, x);
		draw_column_layers(cub, x, ray, cam.focal);
	}
}
/*________TEMP________*/
