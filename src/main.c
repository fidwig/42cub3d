/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:17:45 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/23 18:49:28 by bazaluga         ###   ########.fr       */
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
		&map->tex_nor.bitdepth, &map->tex_nor.linelen, &map->tex_nor.endian);
	map->tex_sou.img = mlx_xpm_file_to_image(mlx, map->tex_sou_name,
		&map->tex_sou.width, &map->tex_sou.height);
	if (!map->tex_sou.img)
		return (false);
	map->tex_sou.addr = mlx_get_data_addr(map->tex_sou.img,
		&map->tex_sou.bitdepth, &map->tex_sou.linelen, &map->tex_sou.endian);
	map->tex_eas.img = mlx_xpm_file_to_image(mlx, map->tex_eas_name,
		&map->tex_eas.width, &map->tex_eas.height);
	if (!map->tex_eas.img)
		return (false);
	map->tex_eas.addr = mlx_get_data_addr(map->tex_eas.img,
		&map->tex_eas.bitdepth, &map->tex_eas.linelen, &map->tex_eas.endian);
	map->tex_wes.img = mlx_xpm_file_to_image(mlx, map->tex_wes_name,
		&map->tex_wes.width, &map->tex_wes.height);
	if (!map->tex_wes.img)
		return (false);
	map->tex_wes.addr = mlx_get_data_addr(map->tex_wes.img,
		&map->tex_wes.bitdepth, &map->tex_wes.linelen, &map->tex_wes.endian);
	return (true);
}

static void	init_cub(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		clean_exit(1, cub);
	get_tex_imgs(cub->mlx, &cub->map);
	cub->image.img = mlx_new_image(cub->mlx, S_WIDTH, S_HEIGHT);
	if (!cub->image.img)
		clean_exit(1, cub);
	cub->image.addr = mlx_get_data_addr(cub->image.img,
			&cub->image.bitdepth, &cub->image.linelen, &cub->image.endian);
	cub->win = mlx_new_window(cub->mlx, S_WIDTH, S_HEIGHT, "cub3d");
	if (!cub->win)
		clean_exit(1, cub);
	cub->player.spd = -1;
	cub->player.pos = (t_dvec3){-1, -1, -1};
	init_info(&cub->info);
}

static int	update(t_cub *cub)
{
	inputs_handler(cub);
	clear_image(&cub->image, BLACK);
	pixel_put(&cub->image, (int)cub->player.pos.x, (int)cub->player.pos.z, 0x65A0C1);
	pixel_put(&cub->image, (int)cub->player.pos.x + cos(cub->player.rot) * 10, (int)cub->player.pos.z + sin(cub->player.rot) * 10, 0x65A0C1);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->image.img, 0, 0);
	update_info(&cub->info);
	return (0);
}

static void	init_hooks(t_cub *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, key_pressed_hook, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_released_hook, cub);
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
	if (!parse_scene(&cub, argv[1]))
		stop_error(1, &cub, "Scene parsing");
	init_cub(&cub);
	init_hooks(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
