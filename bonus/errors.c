/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:33:18 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/08 23:50:44 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

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
	if (cub->map.tex_door.img)
		mlx_destroy_image(cub->mlx, cub->map.tex_door.img);
	if (cub->map.tex_opendoor.img)
		mlx_destroy_image(cub->mlx, cub->map.tex_opendoor.img);
	if (cub->map.tex_ceil.img)
		mlx_destroy_image(cub->mlx, cub->map.tex_ceil.img);
	if (cub->map.tex_floor.img)
		mlx_destroy_image(cub->mlx, cub->map.tex_floor.img);
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

const char	*err_txt(int phase, int err_n)
{
	static const char	*infos[] = {"", "Missing texture(s) and/or \
colour(s)", "Problem getting textures", "Problem getting floor/ceil colours", \
"Unexpected line while getting textures & colours", "Problem getting the map"};
	static const char	*getmap[] = {"", "get_map: No initial player position \
set", "get_map: mem allocation error", "get_map: bad map format: forbidden \
newlines", "get_map: problem creating raw map"};

	if (phase == 0)
		return (infos[err_n]);
	if (phase == 1)
		return (getmap[err_n]);
	return (NULL);
}

int	stop_error(int exit_code, t_cub *cub, const char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (cub)
		clean_exit(exit_code, cub);
	return (exit_code);
}
