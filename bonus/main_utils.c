/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:56:27 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/14 12:02:46 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"
#include "mlx.h"

bool	get_tex_imgs(void *mlx, t_map *map)
{
	void	*p;
	t_image	*img;
	int		step;
	void	*end;

	step = sizeof(t_image);
	p = &map->nor_tex;
	end = &map->sky_tex;
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

bool	get_tex_sprites(t_cub *cub)
{
	int		i;
	t_image	*tex;

	i = 0;
	while (i < cub->sprite_count)
	{
		tex = &cub->sprites[i].tex;
		tex->img = mlx_xpm_file_to_image(cub->mlx, tex->name, &tex->width,
				&tex->height);
		if (!tex->img)
			return (false);
		tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->len,
				&tex->endian);
		i++;
	}
	return (true);
}
