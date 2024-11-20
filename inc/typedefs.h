/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:33:05 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/20 00:32:28 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# define LARR 256
# define RARR 257

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

typedef enum e_dir
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}	t_dir;

typedef struct s_hit
{
	t_vec3		pos;
	float		light;
	t_dir		facing;
	// surface type (wall, door, special wall?)
}	t_hit;

typedef struct s_ray
{
	t_dvec3	dir;
	double	length;
	t_hit	info;
}	t_ray;

typedef struct s_cast_info
{
	t_ray	ray;
	int		flag;
	t_dvec3	pos;
	t_vec3	mpos;
	t_dvec3	side_dist;
	t_dvec3	delta;
	t_vec3	step;
	bool	hit;
}	t_cast_info;

typedef struct s_info
{
	double			framerate;
	double			delta;
	double			runtime;
	unsigned long	start_time;
	unsigned long	last_frame;
}	t_info;

typedef struct s_camera
{
	double	focal;
	t_dvec3	plane;
}	t_camera;

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

#endif // !TYPEDEFS_H
