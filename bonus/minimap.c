/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:43:48 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/20 17:50:11 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	draw_square(t_image *img, t_vec3 pos, int s, unsigned int color)
{
	int	i;
	int	j;

	i = pos.x - 1;
	while (++i < pos.x + s)
	{
		j = pos.y - 1;
		while (++j < pos.y + s)
			pixel_put(img, i, j, color);
	}
}

void	draw_wall(t_cub *cub, int x, int y)
{
	t_vec3	texcoord;
	t_dvec3	offset;
	char	c;

	offset.x = cub->player.pos.x - floor(cub->player.pos.x);
	offset.y = cub->player.pos.z - floor(cub->player.pos.z);
	texcoord.x = (x - 1 - offset.x) * 10;
	texcoord.y = (y - 1 - offset.y) * 10;
	c = cub->map.raw[(int)cub->player.pos.z + y - 6]
	[(int)cub->player.pos.x + x - 6];
	if (c == '1')
		draw_square(&cub->minimap, texcoord, 10,
			(cub->map.col_floor & 0xefefef));
	else if (c == 'D')
		draw_square(&cub->minimap, texcoord, 10, 0x00FF00);
}

void	draw_minimap(t_cub *cub)
{
	int		x;
	int		y;

	clear_image(&cub->minimap, (cub->map.col_floor | 0x101010));
	y = -1;
	while (++y < 12)
	{
		x = -1;
		while (++x < 12)
		{
			if (cub->player.pos.z + y - 6 < 0
				|| cub->player.pos.z + y - 6 >= cub->map.height)
				continue ;
			if (cub->player.pos.x + x - 6 < 0
				|| cub->player.pos.x + x - 6 >= cub->map.width)
				continue ;
			draw_wall(cub, x, y);
		}
	}
	draw_square(&cub->minimap, (t_vec3){48, 48, 0},
		3, 0xffffff - (cub->map.col_floor));
	draw_square(&cub->minimap, (t_vec3){49 + cos(cub->player.yaw) * 5.0,
		49 + sin(cub->player.yaw) * 5.0, 0}, 2,
		0xffffff - (cub->map.col_floor));
}
