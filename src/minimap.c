/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:43:48 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/22 00:55:34 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_square(t_image *img, int x, int y, int s)
{
	int	i;
	int	j;

	i = x - 1;
	while (++i < x + s)
	{
		j = y - 1;
		while (++j < y + s)
			pixel_put(img, i, j, 0x222020);
	}
}

void	draw_minimap(t_cub *cub)
{
	int		x;
	int		y;
	t_dvec3	offset;

	offset.x = cub->player.pos.x - floor(cub->player.pos.x);
	offset.y = cub->player.pos.z - floor(cub->player.pos.z);
	clear_image(&cub->minimap, 0x444040);
	draw_square(&cub->minimap, 48, 48, 3);
	draw_square(&cub->minimap, 49 + cos(cub->player.rot) * 5.0, 49 + sin(cub->player.rot) * 5.0, 2);
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
				draw_square(&cub->minimap, (x - 1 - offset.x) * 10, (y - 1 - offset.y) * 10, 10);
		}
	}
}
