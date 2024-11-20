/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:37:31 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/20 01:28:11 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_ray_info(t_ray *ray, int flag)
{
	if (flag)
	{
		if (ray->dir.y > 0)
			ray->info.facing = NORTH;
		else
			ray->info.facing = SOUTH;
	}
	else
	{
		if (ray->dir.x > 0)
			ray->info.facing = EAST;
		else
			ray->info.facing = WEST;
	}
}

void	cast_init(t_cast_info *cast)
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

void	dda(t_cast_info	*cast, t_map map)
{
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
		cast->hit = (map.raw[cast->mpos.x][cast->mpos.y] == '1');
	}
	if (cast->flag == 0)
		cast->ray.length = cast->side_dist.x - cast->delta.x;
	else
		cast->ray.length = cast->side_dist.y - cast->delta.y;
}

t_ray	cast_ray(t_dvec3 origin, t_dvec3 dir, t_map map)
{
	t_cast_info	cast;

	cast = (t_cast_info){0};
	cast.ray.dir = dir;
	cast.pos = (t_dvec3){origin.x, origin.z, 0};
	cast.mpos = (t_vec3){(int)origin.x, (int)origin.z, 0};
	cast_init(&cast);
	dda(&cast, map);
	set_ray_info(&cast.ray, cast.flag);
	return (cast.ray);
}

void	raycasting(t_cub *cub)
{
	int			i;
	t_ray		ray;
	t_dvec3		ray_dir;
	double		camera_x;
	t_camera	cam;

	cam.focal = tan(deg2rad(FOV / 2.0));
	cam.plane = (t_dvec3){cos(cub->player.rot - M_PI / 2.0) * cam.focal,
		sin(cub->player.rot - M_PI / 2.0) * cam.focal, 0};
	i = 0;
	while (i < SW)
	{
		camera_x = 2.0 * (i / ((double)SW * cam.focal)) - 1.0;
		ray_dir = (t_dvec3){cos(cub->player.rot) + cam.plane.x * camera_x,
			sin(cub->player.rot) + cam.plane.y * camera_x, 0};
		ray = cast_ray(cub->player.pos, ray_dir, cub->map);
		draw_column(cub, i, (int)(SH / ray.length) / cam.focal, ray);
		i++;
	}
}
		/*________TEMP________*/
