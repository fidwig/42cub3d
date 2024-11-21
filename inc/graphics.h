/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:34:30 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/21 09:48:07 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include "typedefs.h"

void			clear_image(t_image *image, t_uicol color);
t_trgb			utorgb(unsigned int color);
unsigned int	rgbtou(t_trgb trgb);
void			pixel_put(t_image *data, int x, int y, int color);

#endif // !GRAPHIX
