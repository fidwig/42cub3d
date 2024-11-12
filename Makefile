NAME		:= cub3D
INCDIR		:= inc
SRCDIR		:= src
MLXDIR		:= mlx
LIBFTDIR	:= libft
MLX			:= $(MLXDIR)/libmlx.a
LIBFT		:= $(LIBFTDIR)/libft.a
OBJDIR		:= .obj/
SRCS		:= main.c raycasting.c graphics.c
OBJS		:= $(SRC:.c=.o)
SRC			:= $(addprefix $(SRCDIR)/, $(SRC))
OBJ			:= $(addprefix $(OBJDIR)/, $(OBJ))
DEPS		:= $(OBJS:.c=.o)

RM		:= rm -rf
CC		:= cc
CFLAGS	:= -Wall -Werror -Wextra -I$(INCDIR) -I$(MLX) -g3

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CPPC) $(CPPFLAGS) -o $@ -c $^

# include $(DEPS)
clean:
	@$(RM) $(OBJS) $(DEPS) $(OBJDIR)
	@make -C $(LIBFTDIR) fclean
	@make -C $(MLXDIR) fclean

fclean: clean
	rm -rf
