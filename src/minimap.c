/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:11:27 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/27 14:31:55 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

void	draw_minimap(t_cub *cub)
{
	int		x;
	int		y;
	t_dvec3	offset;

	offset.x = cub->player.pos.x - floor(cub->player.pos.x);
	offset.y = cub->player.pos.z - floor(cub->player.pos.z);
	clear_image(&cub->minimap, dim_color(cub->map.col_floor + 0x111111, 1));
	draw_square(&cub->minimap, (t_vec3){48, 48, 0}, 3, cub->map.col_ceil);
	draw_square(&cub->minimap, (t_vec3){49 + cos(cub->player.rot) * 5.0, 49 + sin(cub->player.rot) * 5.0, 0}, 2, cub->map.col_ceil);
	y = -1;
	while (++y < 12)
	{
		x = -1;
		while (++x < 12)
		{
			if (cub->player.pos.z + y - 6 < 0 || cub->player.pos.z + y - 6 >= cub->map.height)
				continue ;
			if (cub->player.pos.x + x - 6 < 0 || cub->player.pos.x + x - 6 >= cub->map.width)
				continue ;
			if (cub->map.raw[(int)cub->player.pos.z + y - 6][(int)cub->player.pos.x + x - 6] == '1')
				draw_square(&cub->minimap, (t_vec3){(x - 1 - offset.x) * 10, (y - 1 - offset.y) * 10, 0}, 10, dim_color(cub->map.col_ceil, 0.8));
		}
	}
}
