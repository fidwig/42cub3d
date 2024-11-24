/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:34:30 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/24 17:16:24 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

void			clear_image(t_image *image, t_uicol color);
void			clear_image_bicolor(t_image *image, t_uicol color1,
					t_uicol color2);
void			draw_image(t_image *dest, t_image *src, int x, int y);
t_trgb			utorgb(unsigned int color);
unsigned int	rgbtou(t_trgb trgb);
void			pixel_put(t_image *data, int x, int y, int color);
unsigned int	pixel_get(t_image image, int x, int y);
t_image			create_notex(t_cub *cub);

double			clamp(double n, double mini, double maxi);
void			draw_column(t_cub *cub, int x, int h, t_ray ray);
void			raycasting(t_cub *cub);
void			floorcasting(t_cub *cub);

#endif // !GRAPHIX
