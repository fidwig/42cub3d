/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:58:12 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/21 20:40:09 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

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
# include "typedefs.h"
// ---GRAPHIX
# include "graphics.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define USEC 0
# define MSEC 1

# define S_WIDTH	1280
# define S_HEIGHT	720
# define BLACK		0x000000
# define WHITE		0xFFFFFF

//ERRORZ
void			clean_exit(int exit_code, t_cub *cub);
void			usage_error(void);
void			stop_error(int exit_code, t_cub *cub, const char *msg);

//HOOKS
int				key_pressed_hook(int key, t_cub *cub);
int				key_released_hook(int key, t_cub *cub);

//INPUTS
void			inputs_handler(t_cub *cub);

//INFO
int				init_info(t_info *info);
int				update_info(t_info *info);

//PARSING
int				get_infos(t_cub *cub, int fd);
bool			get_map(t_cub *cub, int fd);


#endif // !CUB_H
