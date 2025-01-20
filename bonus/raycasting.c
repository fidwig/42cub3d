/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:28:12 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/20 17:50:11 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	cam.plane = (t_dvec3){cos(cub->player.yaw - M_PI / 2.0) * cam.focal,
		sin(cub->player.yaw - M_PI / 2.0) * cam.focal, 0};
	x = -1;
	// unsigned long floor = 0;
	// unsigned long a;
	while (++x < SW)
	{
		camera_x = 2.0 * (1 - x / ((double)SW)) - cam.focal;
		ray_dir = (t_dvec3){cos(cub->player.yaw) + cam.plane.x * camera_x,
			sin(cub->player.yaw) + cam.plane.y * camera_x, 0};
		ray = cast_ray(cub->player.pos, ray_dir, cub->map);
		// a = get_now(MSEC);
		floorcasting(cub, ray, x);
		// floor += get_now(MSEC) - a;
		draw_column_layers(cub, x, ray, cam.focal);
	}
	// dprintf(2, "   floor render time:\t%lums\n", floor);
}
	// unsigned long cast = 0;
	// unsigned long walls = 0;
	// dprintf(2, "   raycasting time:\t%lums\n", cast);
	// dprintf(2, "   wall render time:\t%lums\n", walls);
/*________TEMP________*/

		// a = get_now(MSEC);
		// a = get_now(MSEC);
		// walls += get_now(MSEC) - a;
		// cast += get_now(MSEC) - a;