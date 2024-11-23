#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 14:52:38 by bazaluga          #+#    #+#              #
#    Updated: 2024/11/23 15:53:37 by bazaluga         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

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
SRCS		+=	main.c raycasting.c graphics.c graphics_utils.c hooks.c \
				parsing.c parsing_infos.c parsing_map.c errors.c inputs.c \
				runtime_info.c
OBJS		:=	$(SRCS:%.c=%.o)
SRCS		:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS		:=	$(addprefix $(OBJDIR)/, $(OBJS))
DEPS		:=	$(OBJS:.o=.d)

RM		:=	rm -rf
CC		:=	cc
CFLAGS	:=	-Wall -Werror -Wextra -I$(INCDIR) -I$(MLXDIR) -I$(LIBFTDIR) -g3

all: $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(LIBFT): $(LIBFTDIR)
	@make -sC $(LIBFTDIR)

$(MLX): $(MLXDIR)
	@make -sC $(MLXDIR)

$(NAME): $(LIBFT) $(MLX) $(OBJDIR) $(OBJS) Makefile
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MMD -o $@ -c $^

-include: $(DEPS)

clean:
	@$(RM) $(OBJS) $(DEPS) $(OBJDIR)
	@make fclean -C $(LIBFTDIR)
	@make clean -C $(MLXDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean flcean re
