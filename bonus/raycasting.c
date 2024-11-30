/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:37:31 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/04 19:05:06 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	set_ray_info(t_ray ray, t_cast_data cast, t_hit *info)
{
	if (cast.flag)
	{
		if (ray.dir.y > 0)
			info->facing = NORTH;
		else
			info->facing = SOUTH;
	}
	else
	{
		if (ray.dir.x > 0)
			info->facing = EAST;
		else
			info->facing = WEST;
	}
	info->pos = cast.mpos;
	info->flag = cast.flag;
	if (cast.flag)
		info->dist = cast.side_dist.y - cast.delta.y;
	else
		info->dist = cast.side_dist.x - cast.delta.x;
	if (cast.flag)
		info->x_wall = ray.origin.x + info->dist * ray.dir.x;
	else
		info->x_wall = ray.origin.z + info->dist * ray.dir.y;
	info->x_wall -= floor(info->x_wall);
	info->type = cast.map.raw[cast.mpos.y][cast.mpos.x];
}

void	add_ray_info(t_ray ray, t_cast_data cast, t_hit *info)
{
	*info = ray.info[ray.hit_count - 1];
	if (cast.side_dist.x < cast.side_dist.y)
	{
		if (ray.dir.x > 0)
			info->facing = EAST;
		else
			info->facing = WEST;
		info->dist = cast.side_dist.x;
		info->pos.x += cast.step.x;
		info->flag = 0;
	}
	else
	{
		if (ray.dir.y > 0)
			info->facing = NORTH;
		else
			info->facing = SOUTH;
		info->dist = cast.side_dist.y;
		info->pos.y += cast.step.y;
		info->flag = 1;
	}
	if (info->flag)
		info->x_wall = ray.origin.x + info->dist * ray.dir.x;
	else
		info->x_wall = ray.origin.z + info->dist * ray.dir.y;
	info->x_wall -= floor(info->x_wall);
}

void	cast_init(t_cast_data *cast)
{
	cast->delta = (t_dvec3){1e30, 1e30, 0};
	if (cast->ray.dir.x != 0)
		cast->delta.x = fabs(1 / cast->ray.dir.x);
	if (cast->ray.dir.y != 0)
		cast->delta.y = fabs(1 / cast->ray.dir.y);
	if (cast->ray.dir.x < 0)
	{
		cast->step.x = -1;
		cast->side_dist.x = (cast->pos.x - cast->mpos.x) * cast->delta.x;
	}
	else
	{
		cast->step.x = 1;
		cast->side_dist.x = (cast->mpos.x + 1.0 - cast->pos.x) * cast->delta.x;
	}
	if (cast->ray.dir.y < 0)
	{
		cast->step.y = -1;
		cast->side_dist.y = (cast->pos.y - cast->mpos.y) * cast->delta.y;
	}
	else
	{
		cast->step.y = 1;
		cast->side_dist.y = (cast->mpos.y + 1.0 - cast->pos.y) * cast->delta.y;
	}
}

void	dda(t_cast_data	*cast, t_map map)
{
	if (is_see_through(map.raw[cast->mpos.y][cast->mpos.x]))
	{
		cast->flag = (cast->side_dist.x >= cast->side_dist.y);
		cast->side_dist.x += cast->delta.x;
		cast->side_dist.y += cast->delta.y;
		set_ray_info(cast->ray, *cast, &cast->ray.info[cast->ray.hit_count++]);
		cast->side_dist.x -= cast->delta.x;
		cast->side_dist.y -= cast->delta.y;
	}
	while (!cast->hit)
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
			set_ray_info(cast->ray, *cast,
				&cast->ray.info[cast->ray.hit_count]);
			cast->ray.hit_count++;
			cast->hit = (!is_see_through(map.raw[cast->mpos.y][cast->mpos.x])
					|| cast->ray.hit_count >= RAY_DEPTH);
			if (!cast->hit && cast->ray.hit_count < RAY_DEPTH - 1)
			{
				add_ray_info(cast->ray, *cast, &cast->ray.info[cast->ray.hit_count]);
				cast->ray.hit_count++;
			}
		}
	}
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

	cam.focal = tan(deg2rad(FOV / 2.0));
	cam.plane = (t_dvec3){cos(cub->player.rot - M_PI / 2.0) * cam.focal,
		sin(cub->player.rot - M_PI / 2.0) * cam.focal, 0};
	x = -1;
	while (++x < SW)
	{
		camera_x = 2.0 * (1 - x / ((double)SW)) - 1.0;
		ray_dir = (t_dvec3){cos(cub->player.rot) + cam.plane.x * camera_x,
			sin(cub->player.rot) + cam.plane.y * camera_x, 0};
		ray = cast_ray(cub->player.pos, ray_dir, cub->map);
		draw_column_layers(cub, x, ray, cam.focal);
	}
}
/*________TEMP________*/
