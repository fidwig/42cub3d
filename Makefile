# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 14:52:38 by bazaluga          #+#    #+#              #
#    Updated: 2025/01/08 23:50:05 by bazaluga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	cub3D
NAMETMP		:=	.mandatory_tmp
NAMEB		:=	.bonus_tmp
INCDIR		:=	inc
SRCDIR		:=	src

ifeq ($(shell uname), Linux)
	MLXDIR	:=	mlx
	LFLAGS	:=	-L/usr/lib -lXext -lX11 -lm -lz
	SRCS	:=	mlx_compat_linux.c
	BSRCS	:=	mlx_compat_linux.c
else
	MLXDIR	:=	mlx_macos
	LFLAGS	:=	-framework OpenGL -framework AppKit -lm
	SRCS	:=	mlx_compat_macos.c
	BSRCS	:=	mlx_compat_macos.c mlx_compat_macos2.c
endif

LIBFTDIR	:=	libft
MLX			:=	$(MLXDIR)/libmlx.a
LIBFT		:=	$(LIBFTDIR)/libft.a
OBJDIR		:=	.obj
HEADERS		:=	cub.h graphics.h typedefs.h
SRCS		+=	angles.c colors_utils.c errors.c graphics.c	hooks.c				\
				image_utils.c inputs.c lst_get_maxstr.c main.c minimap.c		\
				parsing.c parsing_infos.c parsing_map.c parsing_utils.c			\
				raycasting.c runtime_info.c
OBJS		:=	$(SRCS:.c=.o)
HEADERS		:=	$(addprefix $(INCDIR)/, $(HEADERS))
SRCS		:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS		:=	$(addprefix $(OBJDIR)/, $(OBJS))
DEPS		:=	$(OBJS:.o=.d)

############## BONUS ################

BOBJDIR		:=	.bobj
BONUSDIR	:=	bonus
BSRCS		+=	act_ray.c angles.c colors_utils.c errors.c floorcasting.c		\
				graphics.c graphics_utils.c hooks.c image_utils.c inputs.c		\
				lst_get_maxstr.c main.c main_utils.c minimap.c parsing.c		\
				parsing_infos.c parsing_map.c parsing_map2.c parsing_tex.c		\
				parsing_utils.c raycasting.c raycasting_utils.c	runtime_info.c	\
				sky.c sprites.c	wall_id.c
BOBJS		:=	$(BSRCS:%.c=%.o)
BSRCS		:=	$(addprefix $(BONUSDIR)/, $(BSRCS))
BOBJS		:=	$(addprefix $(BOBJDIR)/, $(BOBJS))
BDEPS		:=	$(BOBJS:.o=.d)

RM			:=	rm -rf
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra -I$(INCDIR) -I$(MLXDIR) -I$(LIBFTDIR) -O2 -ffast-math -fno-builtin -g3

all: $(NAME)

bonus: $(NAMEB)

$(OBJDIR):
	mkdir $(OBJDIR)

$(BOBJDIR):
	mkdir $(BOBJDIR)

$(LIBFT): $(LIBFTDIR)
	@make -sC $(LIBFTDIR)

$(MLX): $(MLXDIR)
	@make -sC $(MLXDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

$(BOBJDIR)/%.o: $(BONUSDIR)/%.c
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

$(NAMETMP):	$(LIBFT) $(MLX) $(OBJDIR) $(OBJS) Makefile
		@rm -f $(NAMEB)
		$(CC) $(CFLAGS) $(MLX) $(LIBFT) $(OBJS) -o $(NAME) $(LFLAGS)
		@touch $(NAMETMP)

$(NAME):	$(NAMETMP)

$(NAMEB):	$(LIBFT) $(MLX) $(BOBJDIR) $(BOBJS)
		@rm -f $(NAMETMP)
		$(CC) $(CFLAGS) $(MLX) $(LIBFT) $(BOBJS) -o $(NAME) $(LFLAGS)
		@touch $(NAMEB)

clean:
	@$(RM) $(OBJDIR) $(BOBJDIR)
	@$(RM) $(NAMEB) $(NAMETMP)
	@make fclean -sC $(LIBFTDIR)
	@make clean -sC $(MLXDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

-include $(DEPS) $(BDEPS)

.PHONY: all clean flcean re bonus
