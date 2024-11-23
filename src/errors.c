/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:33:18 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/23 16:05:05 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include <unistd.h>

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
	(void)cub;
	trash_clear();
	/* mlx_destroy_image(cub->mlx, cub->image.img); */
	/* mlx_destroy_window(cub->mlx, cub->win); */
	/* mlx_destroy_display(cub->mlx); */
	/* free(cub->mlx); */
	/* free_map(cub, &cub->map); */
	exit(exit_code);
}

void	stop_error(int exit_code, t_cub *cub, const char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	clean_exit(exit_code, cub);
}

void	usage_error(void)
{
	ft_putstr_fd("usage error: ./cub3D <path_to_map>\n", 2);
}
