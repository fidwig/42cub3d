/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:33:18 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/19 22:23:50 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "mlx.h"

void	free_map(t_cub *cub, t_map *map)
{
	(void) map;
	(void) cub;
	//free_(map.raw);
	// mlx_destroy_image(cub->mlx, map->tex_nor.img);
	// mlx_destroy_image(cub->mlx, map->tex_eas.img);
	// mlx_destroy_image(cub->mlx, map->tex_sou.img);
	// mlx_destroy_image(cub->mlx, map->tex_wes.img);

	// mlx_destroy_image(cub->mlx, map->tex_ceil.img);
	// mlx_destroy_image(cub->mlx, map->tex_floor.img);
}

void	clean_exit(int exit_code, t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->image.img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx2_destroy_display(cub->mlx);
	free(cub->mlx);
	free_map(cub, &cub->map);
	exit(exit_code);
}

void	usage_error(void)
{
	ft_putstr_fd("usage error: ./cub3D <path_to_map>\n", 2);
}
