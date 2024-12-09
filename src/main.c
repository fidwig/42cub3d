/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:17:45 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/10 00:09:44 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	get_tex_imgs(void *mlx, t_map *map)
{
	map->nor_tex.img = mlx_xpm_file_to_image(mlx, map->nor_tex_name,
			&map->nor_tex.width, &map->nor_tex.height);
	if (!map->nor_tex.img)
		return (false);
	map->nor_tex.addr = mlx_get_data_addr(map->nor_tex.img,
			&map->nor_tex.bpp, &map->nor_tex.len, &map->nor_tex.endian);
	map->sou_tex.img = mlx_xpm_file_to_image(mlx, map->sou_tex_name,
			&map->sou_tex.width, &map->sou_tex.height);
	if (!map->sou_tex.img)
		return (false);
	map->sou_tex.addr = mlx_get_data_addr(map->sou_tex.img,
			&map->sou_tex.bpp, &map->sou_tex.len, &map->sou_tex.endian);
	map->eas_tex.img = mlx_xpm_file_to_image(mlx, map->eas_tex_name,
			&map->eas_tex.width, &map->eas_tex.height);
	if (!map->eas_tex.img)
		return (false);
	map->eas_tex.addr = mlx_get_data_addr(map->eas_tex.img,
			&map->eas_tex.bpp, &map->eas_tex.len, &map->eas_tex.endian);
	map->wes_tex.img = mlx_xpm_file_to_image(mlx, map->wes_tex_name,
			&map->wes_tex.width, &map->wes_tex.height);
	if (!map->wes_tex.img)
		return (false);
	map->wes_tex.addr = mlx_get_data_addr(map->wes_tex.img,
			&map->wes_tex.bpp, &map->wes_tex.len, &map->wes_tex.endian);
	return (true);
}

static void	cub_init(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		stop_error(1, cub, "Mlx init failed");
	if (!get_tex_imgs(cub->mlx, &cub->map))
		stop_error(1, cub, "Openning textures failed");
	cub->image.img = mlx_new_image(cub->mlx, SW, SH);
	if (!cub->image.img)
		stop_error(1, cub, "Image creation failed");
	cub->image.addr = mlx_get_data_addr(cub->image.img,
			&cub->image.bpp, &cub->image.len, &cub->image.endian);
	cub->image.width = SW;
	cub->image.height = SH;
	cub->minimap.img = mlx_new_image(cub->mlx, 100, 100);
	cub->minimap.addr = mlx_get_data_addr(cub->minimap.img,
			&cub->minimap.bpp, &cub->minimap.len, &cub->minimap.endian);
	cub->minimap.width = 100;
	cub->minimap.height = 100;
	cub->win = mlx_new_window(cub->mlx, SW, SH, "cub3d");
	if (!cub->win)
		stop_error(1, cub, "Window creation failed");
	cub->player.spd = 2;
	init_info(&cub->info);
}

static int	update(t_cub *cub)
{
	inputs_handler(cub);
	clear_image_bicolor(&cub->image, cub->map.ceil_col, cub->map.floor_col);
	raycasting(cub);
	draw_minimap(cub);
	draw_image(&cub->image, &cub->minimap, 10, 10);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->image.img, 0, 0);
	update_info(&cub->info);
	return (0);
}

static void	init_hooks(t_cub *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, key_pressed_hook, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_released_hook, cub);
	mlx_hook(cub->win, 17, 0L, clean_exit_hook, cub);
	mlx_loop_hook(cub->mlx, update, cub);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (usage_error(), 1);
	cub = (t_cub){0};
	if (!parse_scene(&cub, argv[1]))
		stop_error(1, &cub, "Scene parsing");
	cub_init(&cub);
	init_hooks(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
