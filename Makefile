NAME		:=	cub3D
INCDIR		:=	inc
SRCDIR		:=	src
MLXDIR		:=	mlx
LIBFTDIR	:=	libft
MLX			:=	$(MLXDIR)/libmlx.a
LIBFT		:=	$(LIBFTDIR)/libft.a
OBJDIR		:=	.obj
HEADERS		:=	cub.h graphics.h typedefs.h
SRCS		:=	main.c raycasting.c graphics.c graphics_utils.c hooks.c \
				parsing.c errors.c inputs.c runtime_info.c angles.c
OBJS		:=	$(SRCS:%.c=%.o)
HEADERS		:=	$(addprefix $(INCDIR)/, $(HEADERS))
SRCS		:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS		:=	$(addprefix $(OBJDIR)/, $(OBJS))
DEPS		:=	$(OBJS:.c=.o)

RM			:=	rm -rf
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra -I$(INCDIR) -I$(MLXDIR) -I$(LIBFTDIR)
LFLAGS		:=	-L/usr/lib -lXext -lX11 -lm -lz

all: $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(LIBFT): $(LIBFTDIR)
	@make -sC $(LIBFTDIR)

$(MLX): $(MLXDIR)
	@make -sC $(MLXDIR)

$(NAME): $(LIBFT) $(MLX) $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $^

-include: $(DEPS)# $(HEADERS)

clean:
	@$(RM) $(OBJS) $(DEPS) $(OBJDIR)
	@make clean -C $(LIBFTDIR)
	@make clean -C $(MLXDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean flcean re
