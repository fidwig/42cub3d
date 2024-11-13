/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:28:12 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/13 01:38:47 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	key_pressed_hook(int key, t_cub *cub)
{
	(void) key;
	/*
	if key is escape
		quit
	if key < 255
		cub->inputs[key] = true;
	*/
	return (0);
}

int	key_released_hook(int key, t_cub *cub)
{
	(void) key;
	/*
	if key < 255
		cub->inputs[key] = false;
	*/
	return (0);
}
