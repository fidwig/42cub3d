/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:33:05 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/19 22:29:28 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# define LARR 256
# define RARR 257

# include <stdbool.h>

typedef unsigned int	t_uicol;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bitdepth;
	int		linelen;
	int		endian;
}	t_image;

typedef struct s_trgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	t;
}	t_trgb;

typedef struct s_dvec3
{
	double	x;
	double	y;
	double	z;
}	t_dvec3;

typedef struct s_vec3
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct s_player
{
	t_dvec3	pos;
	double	rot;
	double	spd;
}	t_player;

typedef struct s_map
{
	char		**raw;
	t_image		tex_nor;
	t_image		tex_sou;
	t_image		tex_eas;
	t_image		tex_wes;

	t_uicol		col_ceil;
	t_uicol		col_floor;
	t_image		tex_ceil;
	t_image		tex_floor;
}	t_map;

typedef struct s_ray
{
	double	angle;
	double	length;
	int		flag;
}	t_ray;

typedef struct s_info
{
	double			framerate;
	double			delta;
	double			runtime;
	unsigned long	start_time;
	unsigned long	last_frame;
}	t_info;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_image		image;
	bool		inputs[258];

	t_player	player;
	t_map		map;

	t_info		info;
}	t_cub;

# ifndef __linux__

enum e_key
{
	XK_Escape = 53,
	XK_Left = 123,
	XK_Right = 124,
	XK_Up = 126,
	XK_Down = 125,
	XK_a = 0,
	XK_d = 2,
	XK_w = 13,
	XK_s = 1
};

# endif

#endif // !TYPEDEFS_H
