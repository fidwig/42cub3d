/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:31:32 by bazaluga          #+#    #+#             */
/*   Updated: 2024/12/04 09:31:51 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_BONUS_H
# define GRAPHICS_BONUS_H
# include "typedefs_bonus.h"

// UTILZ
void			clear_image(t_image *image, t_uicol color);
void			clear_image_bicolor(t_image *image, t_uicol color1,
					t_uicol color2);
void			draw_image(t_image *dest, t_image *src, int x, int y);
t_trgb			utorgb(unsigned int color);
unsigned int	rgbtou(t_trgb trgb);
void			pixel_put(t_image *data, int x, int y, unsigned int color);
unsigned int	pixel_get(t_image image, int x, int y);
t_image			create_notex(t_cub *cub);
t_uicol			dim_color(t_uicol col, double light);
t_uicol			blend_colors(t_uicol b, t_uicol c);

double			clamp(double n, double mini, double maxi);
void			draw_column(t_cub *cub, int x, int h, t_ray ray);
void			draw_column_layers(t_cub *cub, int x, t_ray ray, double focal);
void			raycasting(t_cub *cub);
void			floorcasting(t_cub *cub);

#endif
