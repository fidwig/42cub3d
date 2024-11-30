/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:33:18 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/30 19:54:09 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "mlx.h"

static void	clean_imgs_tex(t_cub *cub)
{
	if (cub->image.img)
		mlx_destroy_image(cub->mlx, cub->image.img);
	if (cub->map.tex_nor.img)
		mlx_destroy_image(cub->mlx, cub->map.tex_nor.img);
	if (cub->map.tex_sou.img)
		mlx_destroy_image(cub->mlx, cub->map.tex_sou.img);
	if (cub->map.tex_eas.img)
		mlx_destroy_image(cub->mlx, cub->map.tex_eas.img);
	if (cub->map.tex_wes.img)
		mlx_destroy_image(cub->mlx, cub->map.tex_wes.img);
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
