/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:26:05 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/16 18:36:51 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	get_sprite_color(t_image tex, t_sdrawing *dr)
{
	if (dr->texcoord.x != dr->ltc.x || dr->texcoord.y != dr->ltc.y)
	{
		dr->col = dim_color(pixel_get(tex,
					dr->texcoord.x, dr->texcoord.y), 1.5);
		dr->ltc = dr->texcoord;
	}
}
