/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:17:45 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/04 19:04:51 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_init(t_cub *cub)
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
	cub->player.spd = 2;
	cub->player.pos = (t_dvec3){3.5, 0, 2.5};
	cub->player.rot = 0;
	if (MOUSE_HIDE)
		mlx_mouse_hide(cub->mlx, cub->win);
	init_info(&cub->info);
}

	// pixel_put(&cub->minimap, cub->player.pos.x * 10.0, cub->player.pos.z * 10.0, 0x65A0C1);
	// pixel_put(&cub->minimap, cub->player.pos.x * 10.0 + cos(cub->player.rot) * 10.0, cub->player.pos.z * 10.0 + sin(cub->player.rot) * 10, 0x65A0C1);
int	update(t_cub *cub)
{
	inputs_handler(cub);
	// clear_image(&cub->image, BLACK);
	clear_image_bicolor(&cub->image, cub->map.col_ceil, cub->map.col_floor);
	// floorcasting(cub);
	raycasting(cub);
	draw_minimap(cub);
	draw_image(&cub->image, &cub->minimap, 10, 10);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->image.img, 0, 0);
	update_info(&cub->info);
	return (0);
}

void	init_hooks(t_cub *cub)
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

	(void) argc;
	(void) argv;
	if (argc < 2)
		return (usage_error(), 1);
	cub = (t_cub){0};
	char *manmap[100] = {
		ft_strdup("111111111111111111111111111111111111"),
		ft_strdup("110000000000000111111111100000000001"),
		ft_strdup("100000000000010000111111100000000001"),
		ft_strdup("100000000000010000000000000000000001"),
		ft_strdup("1110000000D0011111111111100000000001"),
		ft_strdup("1110000000000T1111111111100000000001"),
		ft_strdup("1111111D1111111111111111111111111111"),
		ft_strdup("1111111D1111000000000110000000000001"),
		ft_strdup("111111T01111000000000T10111111111101"),
		ft_strdup("111111101111000000000110100000000101"),
		ft_strdup("11111110T111000000000110101111110101"),
		ft_strdup("111111T01111000000000110101000010101"),
		ft_strdup("111111100000000000000110101111010101"),
		ft_strdup("1111111T1111000000000T10100000010101"),
		ft_strdup("111100000001000000000110111111110101"),
		ft_strdup("11110010000T0000001D1110000000010101"),
		ft_strdup("111100100001111T11101111111111010001"),
		ft_strdup("111100000000000000000000000000011111"),
		ft_strdup("111111111111111111111111111111111111")
	};
	cub.map.raw = manmap;
	cub.map.width = 37;
	cub.map.height = 19;
	cub.map.col_ceil = 0x1a1019;
	cub.map.col_floor = 0x483c3d;
	cub_init(&cub);
	init_hooks(&cub);
	t_image	tmp;
	tmp.img = mlx_xpm_file_to_image(cub.mlx, "./resources/xpm/grass.xpm", &tmp.width, &tmp.height);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.len, &tmp.endian);
	cub.map.tex_nor = tmp;//create_notex(&cub);
	cub.map.tex_eas = tmp;//create_notex(&cub);
	cub.map.tex_sou = tmp;//create_notex(&cub);
	cub.map.tex_wes = tmp;//create_notex(&cub);
	tmp.img = mlx_xpm_file_to_image(cub.mlx, "./resources/xpm/door_tex.xpm", &tmp.width, &tmp.height);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.len, &tmp.endian);
	cub.map.door_tex = tmp;
	tmp.img = mlx_xpm_file_to_image(cub.mlx, "./resources/xpm/dooropen_tex.xpm", &tmp.width, &tmp.height);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.len, &tmp.endian);
	// set_transparency(&tmp, 0xAA);
	cub.map.opendoor_tex = tmp;
	tmp.img = mlx_xpm_file_to_image(cub.mlx, "./resources/xpm/torch_set.xpm", &tmp.width, &tmp.height);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.len, &tmp.endian);
	cub.map.torch_tex = tmp;
	mlx_loop(cub.mlx);
	return (0);
}
