/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:33:05 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/21 23:22:31 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# define LARR 256
# define RARR 257

typedef unsigned int		t_uicol;
typedef struct s_hit		t_hit;
typedef struct s_ray		t_ray;
typedef struct s_cast_data	t_cast_data;
typedef struct s_ray		t_ray;
typedef struct s_image		t_image;
typedef struct s_trgb		t_trgb;
typedef struct s_dvec3		t_dvec3;
typedef struct s_vec3		t_vec3;
typedef struct s_player		t_player;
typedef struct s_map		t_map;
typedef struct s_info		t_info;
typedef struct s_camera		t_camera;
typedef struct s_cub		t_cub;
typedef enum e_dir			t_dir;

struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	int		width;
	int		height;
};

struct s_trgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	t;
};

struct s_dvec3
{
	double	x;
	double	y;
	double	z;
};

struct s_vec3
{
	int	x;
	int	y;
	int	z;
};

struct s_player
{
	t_dvec3	pos;
	double	rot;
	double	spd;
};

struct s_map
{
	char		**raw;
	int			width;
	int			height;

	t_image		tex_nor;
	t_image		tex_sou;
	t_image		tex_eas;
	t_image		tex_wes;

	t_uicol		col_ceil;
	t_uicol		col_floor;
	t_image		tex_ceil;
	t_image		tex_floor;
};

enum e_dir
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

struct s_hit
{
	t_vec3		pos;
	t_dir		facing;
	float		light;
	int			flag;
	double		x_wall;
	char		type; //wall '1', close door 'D', open door 'O', light 'L', etc, special wall?
};

struct s_ray
{
	t_dvec3	dir;
	t_dvec3	origin;
	double	length;
	t_hit	info;
};

struct s_cast_data
{
	t_ray	ray;
	int		flag;
	t_dvec3	pos;
	t_vec3	mpos;
	t_dvec3	side_dist;
	t_dvec3	delta;
	t_vec3	step;
	bool	hit;
};

struct s_info
{
	double			framerate;
	double			delta;
	double			runtime;
	unsigned long	start_time;
	unsigned long	last_frame;
};

struct s_camera
{
	double	focal;
	t_dvec3	plane;
};

struct s_cub
{
	void		*mlx;
	void		*win;
	t_image		image;
	bool		inputs[258];

	t_player	player;
	t_map		map;
	t_image		minimap;

	t_info		info;
};

#endif // !TYPEDEFS_H
