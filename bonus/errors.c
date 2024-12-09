/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:33:18 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/06 14:40:36 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	clean_imgs_tex(t_cub *cub)
{
	if (cub->image.img)
		mlx_destroy_image(cub->mlx, cub->image.img);
	if (cub->map.nor_tex.img)
		mlx_destroy_image(cub->mlx, cub->map.nor_tex.img);
	if (cub->map.sou_tex.img)
		mlx_destroy_image(cub->mlx, cub->map.sou_tex.img);
	if (cub->map.eas_tex.img)
		mlx_destroy_image(cub->mlx, cub->map.eas_tex.img);
	if (cub->map.wes_tex.img)
		mlx_destroy_image(cub->mlx, cub->map.wes_tex.img);
	if (cub->map.door_tex.img)
		mlx_destroy_image(cub->mlx, cub->map.door_tex.img);
	if (cub->map.opendoor_tex.img)
		mlx_destroy_image(cub->mlx, cub->map.opendoor_tex.img);
	if (cub->map.ceil_tex.img)
		mlx_destroy_image(cub->mlx, cub->map.ceil_tex.img);
	if (cub->map.floor_tex.img)
		mlx_destroy_image(cub->mlx, cub->map.floor_tex.img);
	if (cub->minimap.img)
		mlx_destroy_image(cub->mlx, cub->minimap.img);
}

void	clean_exit(int exit_code, t_cub *cub)
{
	clean_imgs_tex(cub);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
		mlx2_destroy_display(cub->mlx);
	trash_clear();
	exit(exit_code);
}

int	clean_exit_hook(t_cub *cub)
{
	clean_exit(EXIT_SUCCESS, cub);
	return (0);
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
