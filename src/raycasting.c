/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:37:31 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/19 20:01:33 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

typedef enum e_cardinal
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}	t_cardinal;

// typedef enum e_wall_type
// {

// }	t_wall_type;

typedef struct s_hit
{
	t_vec3		pos;
	float		light;
	t_cardinal	facing;
	// e_wtype	type;
}	t_hit;


typedef struct s_cast_info
{
	t_ray	ray;
	t_dvec3	pos;
	t_vec3	map_pos;
	t_dvec3	side_dist;
	t_dvec3	delta;
	t_vec3	step;
	t_hit	info;
	bool	hit;
}	t_cast_info;

t_ray	cast_ray(t_player player, t_map map, int i, double rays_angle_delta)
{
	t_cast_info	cast;

	cast.ray.angle = (i - S_WIDTH / 2.0) * (rays_angle_delta) + player.rot;
	cast.pos = (t_dvec3){player.pos.x, player.pos.z, 0};
	// printf("%2f ", cast.ray.angle);
	cast.map_pos = (t_vec3){(int)cast.pos.x, (int)cast.pos.y, 0};
	if (cos(cast.ray.angle) != 0)
		cast.delta.x = fabs(1 / cos(cast.ray.angle));
	else
		cast.delta.x = 1e30;
	if (sin(cast.ray.angle) != 0)
		cast.delta.y = fabs(1 / sin(cast.ray.angle));
	else
		cast.delta.y = 1e30;
	if (cos(cast.ray.angle) < 0)
	{
		cast.step.x = -1;
		cast.side_dist.x = (cast.pos.x - cast.map_pos.x) * cast.delta.x;
	}
	else
	{
		cast.step.x = 1;
		cast.side_dist.x = (cast.map_pos.x + 1.0 - cast.pos.x) * cast.delta.x;
	}
	if (sin(cast.ray.angle) < 0)
	{
		cast.step.y = -1;
		cast.side_dist.y = (cast.pos.y - cast.map_pos.y) * cast.delta.y;
	}
	else
	{
		cast.step.y = 1;
		cast.side_dist.y = (cast.map_pos.y + 1.0 - cast.pos.y) * cast.delta.y;
	}
	cast.hit = false;
	while (!cast.hit)
	{
		if (cast.side_dist.x < cast.side_dist.y)
		{
			cast.side_dist.x += cast.delta.x;
			cast.map_pos.x += cast.step.x;
			cast.ray.flag = 0;
		}
		else
		{
			cast.side_dist.y += cast.delta.y;
			cast.map_pos.y += cast.step.y;
			cast.ray.flag = 1;
		}
		if (map.raw[cast.map_pos.x][cast.map_pos.y] == '1')
			cast.hit = true;
	}
	if (cast.ray.flag == 0)
		cast.ray.length = cast.side_dist.x - cast.delta.x;
	else
		cast.ray.length = cast.side_dist.y - cast.delta.y;
	return (cast.ray);
}

void	raycasting(t_cub *cub)
{
	int		i;
	t_ray	ray;
	double	rays_angle_delta;

	rays_angle_delta = deg2rad(FOV) / S_WIDTH;
	i = 0;
	// ray = cast_ray(cub->player, cub->map, S_WIDTH / 2, rays_angle_delta);
	while (i < S_WIDTH)
	{
		ray = cast_ray(cub->player, cub->map, i, rays_angle_delta);
		// draw_col(ray);
		// if (ray.length < 0.1) ray.length = 0.1;
		unsigned char c = 255 * (1 - ray.length / 20);
		// printf("%f ", ray.length);
		pixel_put(&cub->image, i, 100, rgbtou((t_trgb){c, c, c, 0}));
		i++;
	}
}
