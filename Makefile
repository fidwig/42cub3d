#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 14:52:38 by bazaluga          #+#    #+#              #
#    Updated: 2025/01/13 16:53:15 by jsommet          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		:=	cub3D
NAMETMP		:=	.mandatory_tmp
NAMEB		:=	.bonus_tmp
INCDIR		:=	inc
SRCDIR		:=	src

ifeq ($(shell uname), Linux)
	MLXDIR	:=	mlx
	LFLAGS	:=	-L/usr/lib -lXext -lX11 -lm -lz
	SRCS	:=	mlx_compat_linux.c
else
	MLXDIR	:=	mlx_macos
	LFLAGS	:=	-framework OpenGL -framework AppKit -lm
	SRCS	:=	mlx_compat_macos.c
endif

LIBFTDIR	:=	libft
MLX			:=	$(MLXDIR)/libmlx.a
LIBFT		:=	$(LIBFTDIR)/libft.a
OBJDIR		:=	.obj
HEADERS		:=	cub.h graphics.h typedefs.h
SRCS		+=	angles.c errors.c graphics.c hooks.c inputs.c	\
				main.c minimap.c parsing.c parsing_infos.c parsing_map.c 		\
				parsing_utils.c raycasting.c runtime_info.c colors_utils.c		\
				image_utils.c
OBJS		:=	$(SRCS:.c=.o)
HEADERS		:=	$(addprefix $(INCDIR)/, $(HEADERS))
SRCS		:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS		:=	$(addprefix $(OBJDIR)/, $(OBJS))
DEPS		:=	$(OBJS:.o=.d)
#############################v########
############## BONUS ################
BOBJDIR		:=	.bobj
BONUSDIR	:=	bonus
BSRCS		:=	main.c raycasting.c graphics.c hooks.c			\
				errors.c inputs.c runtime_info.c angles.c		\
				floorcasting.c minimap.c act_ray.c wall_id.c	\
				colors_utils.c image_utils.c sky.c				\
				raycasting_utils.c sprites.c lights.c
BOBJS		:=	$(BSRCS:%.c=%.o)
BSRCS		:=	$(addprefix $(BONUSDIR)/, $(BSRCS))
BOBJS		:=	$(addprefix $(BOBJDIR)/, $(BOBJS))
BDEPS		:=	$(BOBJS:.o=.d)

RM			:=	rm -rf
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra -I$(INCDIR) -I$(MLXDIR) -I$(LIBFTDIR) -O2 -ffast-math -fno-builtin

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
		$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)
		@touch $(NAMETMP)

$(NAME):	$(NAMETMP)

$(NAMEB):	$(LIBFT) $(MLX) $(BOBJDIR) $(BOBJS)
		@rm -f $(NAMETMP)
		$(CC) $(CFLAGS) $(LFLAGS) $(BOBJS) $(MLX) $(LIBFT) -o $(NAME)
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
