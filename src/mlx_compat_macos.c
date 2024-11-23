/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_compat_macos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:06:41 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/19 15:23:45 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../mlx_macos/mlx_int.h"

int	mlx2_destroy_display(mlx_ptr_t *xvar)
{
	mlx_destroy_image(xvar, xvar->font);
	free(xvar);
	return (1);
}
