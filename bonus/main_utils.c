/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:56:27 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/06 14:41:43 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

bool	get_tex_imgs(void *mlx, t_map *map)
{
	void	*p;
	t_image	*img;
	int		step;

	step = sizeof(t_image);
	p = &map->nor_tex;
	void *end = &map->torch_tex;
	while (p <= end)
	{
		img = ((t_image *)p);
		if (img->name)
		{
			img->img = mlx_xpm_file_to_image(mlx, img->name, &img->width,
				&img->height);
			if (!img->img)
				return (false);
			img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len,
				&img->endian);
		}
		p += step;
	}
	return (true);
}
