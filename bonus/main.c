/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:17:45 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/16 19:32:55 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	init_y_dist_lookup_table(t_cub *cub)
{
	int		y;
	double	dist;

	y = 0;
	while (++y < SH)
	{
		dist = SH / (2.0 * y - SH);
		cub->y_dist_lookup[y][0] = dist;
		cub->y_dist_lookup[y][1] = LIGHT_STRENGTH / (0.2 + dist);
	}
}

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
	cub->player.spd = 3;
	cub->player.pos = (t_dvec3){3.5, 0, 2.5};
	cub->player.rot = 0;
	cub->mouse_lock = MOUSE_LOCK;
	init_y_dist_lookup_table(cub);
	if (MOUSE_HIDE)
		mlx_mouse_hide(cub->mlx, cub->win);
	mlx_mouse_show(cub->mlx, cub->win);
	init_info(&cub->info);
}

int	update(t_cub *cub)
{
	// clear_image(&cub->image, BLACK);
	// if (cub->map.sky_tex_name)
	render_sky(cub);
	// else if (!cub->map.ceil_tex_name)
	// 	clear_image_bicolor(&cub->image, 0xFF000000, cub->map.col_floor);
	raycasting(cub);
	inputs_handler(cub);
	draw_sprites(cub);
	draw_minimap(cub);
	draw_image(&cub->image, &cub->minimap, 10, 10);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->image.img, 0, 0);
	update_info(&cub->info);
	mlx_string_put(cub->mlx, cub->win, 15, 25, 0x00FF00, ft_itoa(cub->info.framerate));
	return (0);
}
	// unsigned long a;
	// a = get_now(MSEC);
	// dprintf(2, "sprites render time:\t%lu ms\n\n", get_now(MSEC) - a);

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
		ft_strdup("111111111111111111111111111111111111                                          "),
		ft_strdup("100000000000010000111111100000000001                                          "),
		ft_strdup("110000000000000111111111100000000001                                          "),
		ft_strdup("100000000000010000000000000000000001        111                               "),
		ft_strdup("10100000D0D0011111111111100000000001       10001                              "),
		ft_strdup("10100O000000011111111111100000000001      1000001                             "),
		ft_strdup("1011111D111111111111111111111111111111111100000001                            "),
		ft_strdup("1011111D111100000000011000000000000000000D00000001                            "),
		ft_strdup("10111110111100000000011011111111110111101100000001                            "),
		ft_strdup("101111101111000000000110100000000101  101 1000001                             "),
		ft_strdup("101111101111000000000110101111110101  101  10001                              "),
		ft_strdup("101111101111000000000110101000010101  101   111                               "),
		ft_strdup("101111100000000000000110101111010101  101                                     "),
		ft_strdup("101111111111000000000110100000010101  101                       11111111111111"),
		ft_strdup("101100000001000000000110111111110101  101            1111111111110000000000001"),
		ft_strdup("1011001000010000001D1110000000010001  101            1AD0000000000000000000001"),
		ft_strdup("10110010000111111110111111111101111111101            1111111111110111110111101"),
		ft_strdup("10000000000000000000000000000000000000001                       101   101  101"),
		ft_strdup("10000000000000000000000000000000000000001                       101   101  101"),
		ft_strdup("10000000000000000000000000000000000000001                       101   101  101"),
		ft_strdup("10000000000000000000000000000000000000001                       101   101  101"),
		ft_strdup("10000000000000000000000000000000000000001                       101   101  101"),
		ft_strdup("10000000000000000000000000000000000000001                       101   101  101"),
		ft_strdup("10000000000000000000000000000000000000001                       101   101  101"),
		ft_strdup("10000000000000000000000000000000000000001                       101   101  101"),
		ft_strdup("10000000000000000000000000000000000000001                       101   101  101"),
		ft_strdup("10000000000000000000000000000000000000001                       101   101  101"),
		ft_strdup("10000000000000000000000000000000000000001                       101   101  101"),
		ft_strdup("10000000000000000000000000000000000000001                       101   101  101"),
		ft_strdup("10000000000000000000000000000000000000001                       101   101  101"),
		ft_strdup("101111111111111111111111111111111111111111111111111111111111111110111110111101"),
		ft_strdup("100000000000000000000000000000000000000000000000000000000000000000000000000001"),
		ft_strdup("111111111111111111111111111111111111111111111111111111111111111111111111111111")
	};
	cub.map.raw = manmap;
	cub.map.width = 79;
	cub.map.height = 32;
	cub.map.col_ceil = 0;
	cub.map.col_floor = 0xDD4623;
	cub_init(&cub);
	init_hooks(&cub);
	t_image	tmp;
	tmp.img = mlx_xpm_file_to_image(cub.mlx, "./resources/xpm/walltex.xpm", &tmp.width, &tmp.height);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.len, &tmp.endian);
	cub.map.tex_nor = tmp;//create_notex(&cub);
	cub.map.tex_eas = tmp;//create_notex(&cub);
	cub.map.tex_sou = tmp;//create_notex(&cub);
	cub.map.tex_wes = tmp;//create_notex(&cub);
	tmp.img = mlx_xpm_file_to_image(cub.mlx, "./resources/xpm/floortex.xpm", &tmp.width, &tmp.height);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.len, &tmp.endian);
	cub.map.tex_floor = tmp;
	tmp.img = mlx_xpm_file_to_image(cub.mlx, "./resources/xpm/doortex.xpm", &tmp.width, &tmp.height);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.len, &tmp.endian);
	cub.map.door_tex = tmp;
	tmp.img = mlx_xpm_file_to_image(cub.mlx, "./resources/xpm/doortex_open.xpm", &tmp.width, &tmp.height);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.len, &tmp.endian);
	// set_transparency(&tmp, 0xAA);
	cub.map.opendoor_tex = tmp;
	tmp.img = mlx_xpm_file_to_image(cub.mlx, "./resources/xpm/fire_set.xpm", &tmp.width, &tmp.height);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.len, &tmp.endian);
	cub.map.torch_tex = tmp;
	// cub.notex = create_notex(&cub);
	tmp.img = mlx_xpm_file_to_image(cub.mlx, "./resources/xpm/skytex.xpm", &tmp.width, &tmp.height);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.len, &tmp.endian);
	cub.map.sky_tex = tmp;
	cub.sprite_count = 6;
	cub.sprites = malloc(sizeof(t_sprite) * cub.sprite_count);
	cub.sprites[0] = (t_sprite){(t_dvec3){4.5, 4, 0}, cub.map.torch_tex, 1, (t_vec3){0}};
	cub.sprites[1] = (t_sprite){(t_dvec3){4, 4.5, 0}, cub.map.torch_tex, 1, (t_vec3){0}};
	cub.sprites[2] = (t_sprite){(t_dvec3){4, 3.5, 0}, cub.map.torch_tex, 1, (t_vec3){0}};
	cub.sprites[3] = (t_sprite){(t_dvec3){4, 3, 0}, cub.map.torch_tex, 1, (t_vec3){0}};
	cub.sprites[4] = (t_sprite){(t_dvec3){8, 8, 0}, cub.map.torch_tex, 1, (t_vec3){0}};
	cub.sprites[5] = (t_sprite){(t_dvec3){15, 15, 0}, cub.map.torch_tex, 1, (t_vec3){0}};
	// unsigned long a = get_now(MSEC);
	// while (get_now(MSEC) < a + 1000)
	// 	;
	mlx_loop(cub.mlx);
	return (0);
}
