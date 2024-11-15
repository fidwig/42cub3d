/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:17:45 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/14 18:07:48 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_cub(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->image.img = mlx_new_image(cub->mlx, S_WIDTH, S_HEIGHT);
	cub->image.addr = mlx_get_data_addr(cub->image.img,
			&cub->image.bitdepth, &cub->image.linelen, &cub->image.endian);
	cub->win = mlx_new_window(cub->mlx, S_WIDTH, S_HEIGHT, "cub3d");
	cub->player.spd = 10;
	cub->player.pos = (t_dvec3){200, 0, 200};
	init_info(&cub->info);
}

int	update(t_cub *cub)
{
	inputs_handler(cub);
	clear_image(&cub->image, BLACK);
	pixel_put(&cub->image, (int)cub->player.pos.x, (int)cub->player.pos.z, 0x65A0C1);
	pixel_put(&cub->image, (int)cub->player.pos.x + cos(cub->player.rot) * 10, (int)cub->player.pos.z + sin(cub->player.rot) * 10, 0x65A0C1);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->image.img, 0, 0);
	update_info(&cub->info);
	return (0);
}

void	init_hooks(t_cub *cub)
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
	if (argc < 2)
		return (usage_error(), 1);
	cub = (t_cub){0};
	init_cub(&cub);
	init_hooks(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
