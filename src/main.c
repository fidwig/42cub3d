/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:17:45 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/20 01:46:42 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	cub_init(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->image.img = mlx_new_image(cub->mlx, SW, SH);
	cub->image.addr = mlx_get_data_addr(cub->image.img,
			&cub->image.bitdepth, &cub->image.linelen, &cub->image.endian);
	cub->win = mlx_new_window(cub->mlx, SW, SH, "cub3d");
	cub->player.spd = 2;
	cub->player.pos = (t_dvec3){3, 0, 2};
	cub->player.rot = 0;
	init_info(&cub->info);
}

	// pixel_put(&cub->image, cub->player.pos.x * 10.0, cub->player.pos.z * 10.0, 0x65A0C1);
	// pixel_put(&cub->image, cub->player.pos.x * 10.0 + cos(cub->player.rot) * 10.0, cub->player.pos.z * 10.0 + sin(cub->player.rot) * 10, 0x65A0C1);
int	update(t_cub *cub)
{
	inputs_handler(cub);
	clear_image(&cub->image, BLACK);
	// floor casting (floor and ceiling)
	raycasting(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->image.img, 0, 0);
	update_info(&cub->info);
	return (0);
}

void	init_hooks(t_cub *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, key_pressed_hook, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_released_hook, cub);
	mlx_hook(cub->win, 17, 0L, clean_exit2, cub);
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
		"111111111111111111111111111111111111",
		"110000000000000111111111100000000001",
		"100000000000010000111111100000000001",
		"100000000000010000000000000000000001",
		"111000000010011111111111100000000001",
		"111000000010011111111111100000000001",
		"111111101111111111111111111111111111",
		"111111101111000000000110000000000001",
		"111111101111000000000110111111111101",
		"111111101111000000000110100000000101",
		"111111101111000000000110101111110101",
		"111111101111000000000110101000010101",
		"111111100000000000000110101111010101",
		"111111111111000000000110100000010101",
		"111100000001000000000110111111110101",
		"111100100001000000101110000000010101",
		"111100100001111111101111111111010001",
		"111100000000000000000000000000011111",
		"111111111111111111111111111111111111"
	};
	cub.map.raw = manmap;
	cub_init(&cub);
	init_hooks(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
