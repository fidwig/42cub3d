/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:17:45 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/10 15:00:33 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

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
	if (MOUSE_HIDE)
		mlx_mouse_hide(cub->mlx, cub->win);
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
	mlx_hook(cub->win, 6, 1L << 6, &mouse_event_hook, cub);
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
