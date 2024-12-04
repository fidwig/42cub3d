/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:17:45 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/04 10:14:40 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "mlx.h"

static bool	get_tex_imgs(void *mlx, t_map *map)
{
	map->tex_nor.img = mlx_xpm_file_to_image(mlx, map->tex_nor_name,
			&map->tex_nor.width, &map->tex_nor.height);
	if (!map->tex_nor.img)
		return (false);
	map->tex_nor.addr = mlx_get_data_addr(map->tex_nor.img,
			&map->tex_nor.bpp, &map->tex_nor.len, &map->tex_nor.endian);
	map->tex_sou.img = mlx_xpm_file_to_image(mlx, map->tex_sou_name,
			&map->tex_sou.width, &map->tex_sou.height);
	if (!map->tex_sou.img)
		return (false);
	map->tex_sou.addr = mlx_get_data_addr(map->tex_sou.img,
			&map->tex_sou.bpp, &map->tex_sou.len, &map->tex_sou.endian);
	map->tex_eas.img = mlx_xpm_file_to_image(mlx, map->tex_eas_name,
			&map->tex_eas.width, &map->tex_eas.height);
	if (!map->tex_eas.img)
		return (false);
	map->tex_eas.addr = mlx_get_data_addr(map->tex_eas.img,
			&map->tex_eas.bpp, &map->tex_eas.len, &map->tex_eas.endian);
	map->tex_wes.img = mlx_xpm_file_to_image(mlx, map->tex_wes_name,
			&map->tex_wes.width, &map->tex_wes.height);
	if (!map->tex_wes.img)
		return (false);
	map->tex_wes.addr = mlx_get_data_addr(map->tex_wes.img,
			&map->tex_wes.bpp, &map->tex_wes.len, &map->tex_wes.endian);
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
	clear_image_bicolor(&cub->image, cub->map.col_ceil, cub->map.col_floor);
	// floorcasting(cub);
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

	(void) argc;
	(void) argv;
	if (argc != 2)
		return (usage_error(), 1);
	cub = (t_cub){0};
	// cub.map.col_ceil = DARKRED;
	// cub.map.col_floor = BLACK;
	if (!parse_scene(&cub, argv[1]))
		stop_error(1, &cub, "Scene parsing");
	cub_init(&cub);
	init_hooks(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
