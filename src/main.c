/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:17:45 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/21 21:25:00 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "mlx.h"

void	free_mlx_display(void *cub)
{
	mlx_destroy_display(((t_cub *)cub)->mlx);
}

void	free_mlx_image(void *cub)
{
	mlx_destroy_image(((t_cub *)cub)->mlx, ((t_cub *)cub)->image.img);
}

void	free_mlx_win(void *cub)
{
	mlx_destroy_window(((t_cub *)cub)->mlx, ((t_cub *)cub)->win);
}

void	init_cub(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (clean_exit(1, cub));
	trash_add(cub->mlx, &free_mlx_display);
	cub->image.img = mlx_new_image(cub->mlx, S_WIDTH, S_HEIGHT);
	if (!cub->image.img)
		return (clean_exit(1, cub));
	trash_add(cub->image.img, &free_mlx_image);
	cub->image.addr = mlx_get_data_addr(cub->image.img,
			&cub->image.bitdepth, &cub->image.linelen, &cub->image.endian);
	cub->win = mlx_new_window(cub->mlx, S_WIDTH, S_HEIGHT, "cub3d");
	if (!cub->win)
		return (clean_exit(1, cub));
	trash_add(cub->win, &free_mlx_win);
	cub->player.spd = -1;
	cub->player.pos = (t_dvec3){-1, -1, -1};
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
