/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:17:45 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/13 01:20:21 by jsommet          ###   ########.fr       */
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
}

int	update(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->image.img, 0, 0);
	return (0);
}

void	init_hooks(t_cub *cub)
{
	mlx_loop_hook(cub->mlx, update, cub);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	(void) argc;
	(void) argv;
	cub = (t_cub){0};
	init_cub(&cub);
	init_hooks(&cub);
	mlx_loop(cub.mlx);
}
