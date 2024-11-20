/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:34:30 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/20 00:33:37 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

void			clear_image(t_image *image, t_uicol color);
t_trgb			utorgb(unsigned int color);
unsigned int	rgbtou(t_trgb trgb);
void			pixel_put(t_image *data, int x, int y, int color);

void			draw_column(t_cub *cub, int x, int height, t_ray ray);
void			raycasting(t_cub *cub);

#endif // !GRAPHIX
