/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:28:12 by jsommet           #+#    #+#             */
/*   Updated: 2024/12/12 17:31:49 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	key_pressed_hook(int key, t_cub *cub)
{
	if (key == XK_Escape)
		clean_exit(EXIT_SUCCESS, cub);
	if (key == XK_l)
		cub->mouse_lock = !cub->mouse_lock;
	if (key < 255)
		cub->inputs[key] = true;
	if (key == XK_Left)
		cub->inputs[LARR] = true;
	if (key == XK_Right)
		cub->inputs[RARR] = true;
	return (0);
}

int	key_released_hook(int key, t_cub *cub)
{
	if (key < 255)
		cub->inputs[key] = false;
	if (key == XK_Left)
		cub->inputs[LARR] = false;
	if (key == XK_Right)
		cub->inputs[RARR] = false;
	return (0);
}

int	mouse_event_hook(int x, int y, t_cub *cub)
{
	static int	old_x;

	(void)y;
	if (cub->mouse_lock)
		cub->mouse_movement = x - (SW / 2);
	else
	{
		cub->mouse_movement = x - old_x;
		old_x = x;
	}
	return (0);
}
