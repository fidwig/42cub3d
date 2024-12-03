# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 14:52:38 by bazaluga          #+#    #+#              #
#    Updated: 2024/12/03 15:38:04 by bazaluga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	cub3D
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
SRCS		+=	angles.c errors.c graphics.c graphics_utils.c hooks.c inputs.c \
				main.c minimap.c parsing.c parsing_infos.c parsing_map.c \
				parsing_utils.c raycasting.c runtime_info.c
OBJS		:=	$(SRCS:.c=.o)
HEADERS		:=	$(addprefix $(INCDIR)/, $(HEADERS))
SRCS		:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS		:=	$(addprefix $(OBJDIR)/, $(OBJS))
DEPS		:=	$(OBJS:.o=.d)
#############################v########
############## BONUS ################
BOBJDIR		:=	.bobj
BONUSDIR	:=	bonus
BSRCS	:=	main.c raycasting.c graphics.c graphics_utils.c hooks.c \
				parsing.c errors.c inputs.c runtime_info.c angles.c		\
				floorcasting.c minimap.c act_ray.c wall_id.c
BOBJS	:=	$(BSRCS:%.c=%.o)
BSRCS	:=	$(addprefix $(BONUSDIR)/, $(BSRCS))
BOBJS	:=	$(addprefix $(BOBJDIR)/, $(BOBJS))
BDEPS	:=	$(BOBJS:.o=.d)

RM			:=	rm -rf
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra -I$(INCDIR) -I$(MLXDIR) -I$(LIBFTDIR) -g3

all: $(NAME)

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

$(NAME): $(LIBFT) $(MLX) $(OBJDIR) $(OBJS) Makefile
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(MLX) $(BOBJDIR) $(BOBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(BOBJS) $(MLX) $(LIBFT) -o $(NAME)

clean:
	@$(RM) $(OBJDIR) $(BOBJDIR)
	@make fclean -C $(LIBFTDIR)
	@make clean -C $(MLXDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

-include $(DEPS) $(BDEPS)

.PHONY: all clean flcean re bonus
