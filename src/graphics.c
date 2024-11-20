/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:32:29 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/20 01:45:12 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	clamp(double n, double mini, double maxi)
{
	if (n < mini)
		n = mini;
	if (n > maxi)
		n = maxi;
	return (n);
}

void	draw_column(t_cub *cub, int x, int height, t_ray ray)
{
	int		j;
	t_trgb	col;

	if (height > SH)
		height = SH;
	if (ray.info.facing == NORTH)
		col = utorgb(0xd4a1dd);
	else if (ray.info.facing == EAST)
		col = utorgb(0xb888bd);
	else if (ray.info.facing == SOUTH)
		col = utorgb(0x69a2d1);
	else if (ray.info.facing == WEST)
		col = utorgb(0x688dab);
	col.r = clamp(col.r * (1 - (ray.length / 200)), 0, 255);
	col.g = clamp(col.g * (1 - (ray.length / 200)), 0, 255);
	col.b = clamp(col.b * (1 - (ray.length / 200)), 0, 255);
	j = 0;
	while (j < height)
	{
		pixel_put(&cub->image, x, (SH / 2 - height / 2) + j, rgbtou(col));
		j++;
	}
}
