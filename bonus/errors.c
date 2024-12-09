/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:33:18 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/09 16:28:37 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	free_map(t_cub *cub, t_map *map)
{
	(void) map;
	(void) cub;
}

void	clean_exit(int exit_code, t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->image.img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free_map(cub, &cub->map);
	exit(exit_code);
}

int	clean_exit_hook(t_cub *cub)
{
	clean_exit(EXIT_SUCCESS, cub);
	return (0);
}

void	usage_error(void)
{
	ft_putstr_fd("usage error: ./cub3D <path_to_map>\n", 2);
}
