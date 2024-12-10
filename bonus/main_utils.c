/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:56:27 by bazaluga          #+#    #+#             */
/*   Updated: 2024/12/10 14:55:29 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

/* bool	get_tex_imgs(void *mlx, t_map *map) */
/* {//need to add ceil/floor & doors & doors_open */
/* 	map->nor_tex.img = mlx_xpm_file_to_image(mlx, map->nor_tex_name, */
/* 			&map->nor_tex.width, &map->nor_tex.height); */
/* 	if (!map->nor_tex.img) */
/* 		return (false); */
/* 	map->nor_tex.addr = mlx_get_data_addr(map->nor_tex.img, */
/* 			&map->nor_tex.bpp, &map->nor_tex.len, &map->nor_tex.endian); */
/* 	map->sou_tex.img = mlx_xpm_file_to_image(mlx, map->sou_tex_name, */
/* 			&map->sou_tex.width, &map->sou_tex.height); */
/* 	if (!map->sou_tex.img) */
/* 		return (false); */
/* 	map->sou_tex.addr = mlx_get_data_addr(map->sou_tex.img, */
/* 			&map->sou_tex.bpp, &map->sou_tex.len, &map->sou_tex.endian); */
/* 	map->eas_tex.img = mlx_xpm_file_to_image(mlx, map->eas_tex_name, */
/* 			&map->eas_tex.width, &map->eas_tex.height); */
/* 	if (!map->eas_tex.img) */
/* 		return (false); */
/* 	map->eas_tex.addr = mlx_get_data_addr(map->eas_tex.img, */
/* 			&map->eas_tex.bpp, &map->eas_tex.len, &map->eas_tex.endian); */
/* 	map->wes_tex.img = mlx_xpm_file_to_image(mlx, map->wes_tex_name, */
/* 			&map->wes_tex.width, &map->wes_tex.height); */
/* 	if (!map->wes_tex.img) */
/* 		return (false); */
/* 	map->wes_tex.addr = mlx_get_data_addr(map->wes_tex.img, */
/* 			&map->wes_tex.bpp, &map->wes_tex.len, &map->wes_tex.endian); */
/* 	return (true); */
/* } */

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
