/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:33:18 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/30 13:14:28 by bazaluga         ###   ########.fr       */
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
	if (cub->map.floor_tex.img)
		mlx_destroy_image(cub->mlx, cub->map.floor_tex.img);
	if (cub->map.sky_tex.img)
		mlx_destroy_image(cub->mlx, cub->map.sky_tex.img);
	if (cub->minimap.img)
		mlx_destroy_image(cub->mlx, cub->minimap.img);
}

void	clean_exit(int exit_code, t_cub *cub)
{
	int	i;

	clean_imgs_tex(cub);
	if (cub->pars_data && cub->pars_data->lstsprites)
		ft_lstclear(&cub->pars_data->lstsprites, &free);
	if (cub->pars_data && cub->pars_data->line)
		free(cub->pars_data->line);
	if (cub->sprites)
	{
		i = 0;
		while (i < cub->sprite_count)
		{
			if (cub->sprites[i].tex.img)
				mlx_destroy_image(cub->mlx, cub->sprites[i].tex.img);
			i++;
		}
	}
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
	static const char	*infos[] = {"", "Unexpected line while getting textures \
& colours", "Duplicate texture or colour", "Unable to open texture file",
		"Problem getting floor/ceil colours"};
	static const char	*checkinfos[] = {"", "Missing wall texture", "Duplicate \
ceil: found colour + texture", "Duplicate floor: found colour + texture",
		"Missing ceil or sky texture/colour", "Missing floor texture/colour",
		"Use of sky & ceil textures at the same time forbidden", "Door texture \
set but no open door", "Open door texture set but no door"};
	static const char	*getmap[] = {"", "get_lstmap: No initial player \
position set", "get_lstmap: mem allocation error", "get_lstmap: bad map format: \
forbidden character", "lst_to_map: mem allocation error for map", "lst_to_map: \
mem allocation error for a line", "lst_to_sprites: mem allocation error for \
sprites array"};

	if (phase == 0 && (unsigned long)err_n < sizeof(infos))
		return (infos[err_n]);
	if (phase == 1 && (unsigned long)err_n < sizeof(checkinfos))
		return (checkinfos[err_n]);
	if (phase == 2 && (unsigned long)err_n < sizeof(getmap))
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
