/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:24:14 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/09 14:56:25 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_BONUS_H
# define TYPEDEFS_BONUS_H

# define LARR 256
# define RARR 257
# define RAY_DEPTH 15
# define SW	1280
# define SH	720

# include <stdbool.h>

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

# define MAPCHARS "10NSEWDO "

enum e_mapchars
{
	WALL = '1',
	EMPTY = '0',
	N = 'N',
	S = 'S',
	E = 'E',
	W = 'W',
	DOOR = 'D',
	DOOR_OPEN = 'O',
	SPACE = ' ',
	TMPEMPTY = '9'
};

struct s_image
{
	char	*name;
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
	t_dvec3	upos;
	double	rot;
	double	spd;
};

struct s_map
{
	char		**raw;
	int			width;
	int			height;

	t_uicol		nor_col;
	t_uicol		sou_col;
	t_uicol		eas_col;
	t_uicol		wes_col;
	t_uicol		col_ceil;
	t_uicol		col_floor;
	t_image		tex_nor;
	t_image		tex_sou;
	t_image		tex_eas;
	t_image		tex_wes;
	t_image		tex_ceil;
	t_image		tex_floor;
	t_image		tex_door;
	t_image		tex_opendoor;
	t_image		tex_sky;
	bool		ceil_set;
	bool		floor_set;
	bool		sky_set;
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
	double		dist;
	t_vec3		pos;
	t_dir		facing;
	float		light;
	int			flag;
	double		x_wall;
	char		type;
};

struct s_ray
{
	t_dvec3	dir;
	t_dvec3	origin;
	double	length;
	int		hits;
	t_hit	info[RAY_DEPTH];
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
	t_map	map;
	bool	hit;
};

struct s_info
{
	double			framerate;
	double			delta;
	double			runtime;
	unsigned long	start_time;
	unsigned long	last_frame;
	unsigned long	frame_count;
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
	double		mouse_movement;
	bool		mouse_lock;

	double		y_dist_lookup[SH][2];
	double		z_buffer[SW];

	t_player	player;
	t_map		map;
	t_image		minimap;

	t_image		notex;
	t_info		info;
};

# ifndef __linux__

enum e_key
{
	XK_Escape = 53,
	XK_space = 49,
	XK_Left = 123,
	XK_Right = 124,
	XK_Up = 126,
	XK_Down = 125,
	XK_a = 0,
	XK_d = 2,
	XK_w = 13,
	XK_s = 1,
	XK_l = 37
};

# endif

#endif
