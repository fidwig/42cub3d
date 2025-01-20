/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:28:12 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/20 17:48:24 by jsommet          ###   ########.fr       */
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
	static int	old_y;

	(void)y;
	if (cub->mouse_lock)
	{
		cub->mouse_movement.x = x - (SW / 2);
		cub->mouse_movement.y = y - (SW / 2);
	}
	else
	{
		cub->mouse_movement.x = x - old_x;
		cub->mouse_movement.y = y - old_y;
		old_x = x;
		old_y = y;
	}
	return (0);
}
