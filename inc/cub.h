/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:58:12 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/13 01:36:40 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
// MLX
# include "mlx.h"
# include "mlx_int.h"
// MY HEADERS
// # include "graphics.h" no more

# define S_WIDTH	1280
# define S_HEIGHT	720
# define BLACK		0x000000
# define WHITE		0xFFFFFF

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bitdepth;
	int		linelen;
	int		endian;
}	t_image;

typedef struct s_rgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	t;
}	t_rgb;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_player
{
	t_vec3	pos;
	double	angle;
}	t_player;

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	bool	inputs[256];

	t_image	image;

}	t_cub;

//GRAPHIX
t_rgb			utorgb(unsigned int color);
unsigned int	rgbtou(t_rgb rgb);
void			my_mlx_pixel_put(t_image *data, int x, int y, int color);

//ERRORZ
void			usage_error(void);

//HOOKS
int				key_pressed_hook(int key, t_cub *cub);
int				key_released_hook(int key, t_cub *cub);

#endif // !CUB_H
