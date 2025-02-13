/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_compat_linux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:13:51 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/08 14:29:46 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx_int.h"
#include "../mlx/mlx.h"

int	mlx2_destroy_display(t_xvar *xvar)
{
	mlx_destroy_display(xvar);
	free(xvar);
	return (1);
}

int	mlx2_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y)
{
	return (mlx_mouse_move(mlx_ptr, win_ptr, x, y));
}

int	mlx2_mouse_hide(void *mlx_ptr, void *win_ptr)
{
	return (mlx_mouse_hide(mlx_ptr, win_ptr));
}
