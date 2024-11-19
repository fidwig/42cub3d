/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:37:31 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/19 22:07:14 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_ray_info(t_ray *ray, int flag)
{
	if (flag)
	{
		if (sin(ray->angle) > 0)
			ray->info.facing = NORTH;
		else
			ray->info.facing = SOUTH;
	}
	else
	{
		if (cos(ray->angle) > 0)
			ray->info.facing = EAST;
		else
			ray->info.facing = WEST;
	}
}

void	cast_init(t_cast_info *cast)
{
	cast->delta = (t_dvec3){1e30, 1e30, 0};
	if (cos(cast->ray.angle) != 0)
		cast->delta.x = fabs(1 / cos(cast->ray.angle));
	if (sin(cast->ray.angle) != 0)
		cast->delta.y = fabs(1 / sin(cast->ray.angle));
	if (cos(cast->ray.angle) < 0)
	{
		cast->step.x = -1;
		cast->side_dist.x = (cast->pos.x - cast->mpos.x) * cast->delta.x;
	}
	else
	{
		cast->step.x = 1;
		cast->side_dist.x = (cast->mpos.x + 1.0 - cast->pos.x) * cast->delta.x;
	}
	if (sin(cast->ray.angle) < 0)
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

t_ray	cast_ray(t_dvec3 origin, double angle, t_map map)
{
	t_cast_info	cast;

	// -------- FOR FISHEYE CORRECTION --------
	//calculate ray position and direction
	// double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
	// double rayDirX = dirX + planeX * cameraX;
	// double rayDirY = dirY + planeY * cameraX;

	cast = (t_cast_info){0};
	cast.ray.angle = angle;
	cast.pos = (t_dvec3){origin.x, origin.z, 0};
	cast.mpos = (t_vec3){(int)origin.x, (int)origin.z, 0};
	cast_init(&cast);
	dda(&cast, map);
	set_ray_info(&cast.ray, cast.flag);
	return (cast.ray);
}

void	raycasting(t_cub *cub)
{
	int		i;
	t_ray	ray;
	double	rays_angle_delta;
	double	ray_angle;

	rays_angle_delta = deg2rad(FOV) / S_WIDTH;
	i = 0;
	while (i < S_WIDTH)
	{
		ray_angle = (i - S_WIDTH / 2.0) * (rays_angle_delta) + cub->player.rot;
		ray = cast_ray(cub->player.pos, ray_angle, cub->map);
		ray.length *= pow(cos(ray_angle - cub->player.rot), 0.65);
		int lineheight = (int)(S_HEIGHT / ray.length);
		if (lineheight > S_HEIGHT) lineheight = S_HEIGHT;
		int j = 0;
		t_trgb col;
		if (ray.info.facing == NORTH) col = utorgb(0xA52341);
		else if (ray.info.facing == EAST) col = utorgb(0x67A523);
		else if (ray.info.facing == SOUTH) col = utorgb(0x4167A5);
		else if (ray.info.facing == WEST) col = utorgb(0x234167);
		col.r *= 1 - (ray.length / 15);
		col.g *= 1 - (ray.length / 15);
		col.b *= 1 - (ray.length / 15);
		while (j < lineheight)
		{
			pixel_put(&cub->image, i, (S_HEIGHT / 2 - lineheight / 2) + j, rgbtou(col));
			j++;
		}
		i++;
	}
}
