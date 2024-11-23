/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_compat_linux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:13:51 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/19 15:22:36 by bazaluga         ###   ########.fr       */
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
