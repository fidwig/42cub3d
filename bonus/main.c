/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:17:45 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/07 20:50:31 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	init_y_dist_lookup_table(t_cub *cub)
{
	int		y;
	double	dist;

	y = 0;
	while (++y < SH)
	{
		dist = SH / (2.0 * y - SH);
		cub->y_dist_lookup[y][0] = dist;
		cub->y_dist_lookup[y][1] = pow((1.0 - (dist / 18)), 2);
	}
}

static void	cub_init(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->image.img = mlx_new_image(cub->mlx, SW, SH);
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
	cub->player.spd = 3;
	cub->player.pos = (t_dvec3){3.5, 0, 2.5};
	cub->player.rot = 0;
	cub->mouse_lock = MOUSE_LOCK;
	init_y_dist_lookup_table(cub);
	if (MOUSE_HIDE)
		mlx_mouse_hide(cub->mlx, cub->win);
	init_info(&cub->info);
}

static int	update(t_cub *cub)
{
	inputs_handler(cub);
	render_sky(cub);
	// clear_image_bicolor(&cub->image, 0xFF000000, cub->map.col_floor);
	raycasting(cub);
	draw_minimap(cub);
	draw_sprites(cub);
	draw_image(&cub->image, &cub->minimap, 10, 10);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->image.img, 0, 0);
	update_info(&cub->info);
	mlx_string_put(cub->mlx, cub->win, 15, 25, 0x00FF00, ft_itoa(cub->info.framerate));
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
