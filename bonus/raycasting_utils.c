/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:55:58 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/13 19:31:43 by jsommet          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub_bonus.h"

void	set_ray_info(t_ray ray, t_cast_data cast, t_hit *info)
{
	if (cast.flag && ray.dir.y > 0)
		info->facing = NORTH;
	else if (cast.flag)
		info->facing = SOUTH;
	else if (!cast.flag && ray.dir.x > 0)
		info->facing = EAST;
	else
		info->facing = WEST;
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
	*info = ray.info[ray.hits - 1];
	info->flag = cast.side_dist.x >= cast.side_dist.y;
	if (info->flag)
	{
		if (ray.dir.y > 0)
			info->facing = NORTH;
		else
			info->facing = SOUTH;
		info->dist = cast.side_dist.y;
		info->pos.y += cast.step.y;
	}
	else
	{
		if (ray.dir.x > 0)
			info->facing = EAST;
		else
			info->facing = WEST;
		info->dist = cast.side_dist.x;
		info->pos.x += cast.step.x;
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
