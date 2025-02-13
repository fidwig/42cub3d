/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:23:02 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/30 14:07:33 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

# ifndef __USE_MISC
#  define __USE_MISC
# endif
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/types.h>
// MLX
# include "mlx.h"
# ifdef __linux__
#  include "mlx_int.h"
# endif
// LIBFT
# include "libft.h"
// MY HEADERS
// ---TYPES
# include "typedefs_bonus.h"
// ---GRAPHIX
# include "graphics_bonus.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define USEC 0
# define MSEC 1
# define DEBUG 0
// FIXED_FRAMERATE < 1 : unlimited
# define FIXED_FRAMERATE 0

# define SKY_HEIGHT 360 //SH / 2 but this shit norm wont allow it

# define BLACK		0x000000
# define WHITE		0xFFFFFF
# define DARKRED	0x802020
# define MOUSE_LOCK	0
# define MOUSE_HIDE	0

// COMPATIBILITY
int				mlx2_destroy_display(void *xvar);
int				mlx2_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y);
int				mlx2_mouse_hide(void *mlx_ptr, void *win_ptr);

# define FOV			90
# define HB_STRENGTH	8
# define LIGHT_STRENGTH 1
# define LIGHT_RANGE	8
// # define LIGHT_TINT	0x22FF44
// # define LIGHT_TINT	0xccffff
// # define LIGHT_TINT	0xFD6D1C
// # define LIGHT_TINT	0x4444ED
# define LIGHT_TINT	0xffac70
// # define LIGHT_TINT	0x1234ff

// ERRORZ
void			clean_exit(int exit_code, t_cub *cub);
int				clean_exit_hook(t_cub *cub);
int				stop_error(int exit_code, t_cub *cub, const char *msg);
const char		*err_txt(int phase, int err_n);

// HOOKS
int				key_pressed_hook(int key, t_cub *cub);
int				key_released_hook(int key, t_cub *cub);
int				mouse_event_hook(int x, int y, t_cub *cub);

// INPUTS
void			inputs_handler(t_cub *cub);

// INFO
int				init_info(t_info *info);
int				update_info(t_info *info);
unsigned long	get_now(int unit);

// MINIMAP
void			draw_minimap(t_cub *cub);

// ANGLE MATH
double			wrap_angle(double angle);
double			deg2rad(int deg);
double			dotp(t_dvec3 a, t_dvec3 b);
t_dvec3			a2dv(double angle);

// RACASTING
void			set_ray_info(t_ray ray, t_cast_data cast, t_hit *info);
void			cast_init(t_cast_data *cast);
void			dda(t_cast_data	*cast, t_map map);
t_ray			cast_ray(t_dvec3 origin, t_dvec3 dir, t_map map);
void			set_ray_info(t_ray ray, t_cast_data cast, t_hit *info);
void			add_ray_info(t_ray ray, t_cast_data cast, t_hit *info);

double			dist(t_dvec3 a, t_dvec3 b);
double			compute_light(double d);
double			get_light(t_cub *cub, t_dvec3 tar);
// double			get_light(t_cub *cub, t_dvec3 tar, double light);

void			init_fcdat(t_cub *cub, t_fcdat *fc, int y);
// ACTIONS
void			act_ray(t_cub *cub);

int				is_wall(char c);
int				is_door(char c);
int				is_see_through(char c);
int				is_torch(char c);
int				is_prop(char c);
int				is_visible(char c);

// PARSING
bool			empty_line(char *line);
char			*ft_strtrim_free(const char *str, const char *charset);
int				get_infos(t_cub *cub, t_pars_data *d);
int				lst_to_map(t_cub *cub, t_list *lines, int size);
int				get_map(t_cub *cub, t_pars_data *d);
int				parse_scene(t_cub *cub, char *map_name);
int				check_infos(t_cub *cub);
int				get_texture(t_cub *cub, t_pars_data *d, char *line);
int				save_sprite(t_pars_data *d, int row, int col);
int				lst_to_sprites(t_cub *cub, t_pars_data *d);

// MAIN UTILZ
bool			get_tex_imgs(void *mlx, t_map *map);
bool			get_tex_sprites(t_cub *cub);

// UTILZ
size_t			lst_get_maxstr(t_list *lst);

#endif
