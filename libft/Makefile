NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_abs.c ft_atol.c ft_atou_base.c ft_isspace.c ft_lstremove.c ft_lstunlink.c ft_max_arr.c ft_max.c ft_min_arr.c ft_min.c ft_splitf.c ft_splitlen.c ft_strcmp.c ft_strcpy.c ft_strdup_free.c ft_strjoin_free.c ft_strndup.c \
		ft_strtoll.c \
		get_next_line.c \
		get_next_line_utils.c \
		gc_calloc.c \
		gc_itoa.c \
		gc_lstclear.c \
		gc_lstdelone.c \
		gc_lstmap.c \
		gc_lstnew.c \
		gc_lstremove.c \
		gc_split.c \
		gc_strdup.c \
		gc_strdup_free.c \
		gc_strjoin.c \
		gc_strjoin_free.c \
		gc_strtrim.c \
		gc_substr.c \
		garbage_collector.c \
		garbage_collector_utils.c \
		ft_dprintf.c \
		ft_printf.c \
		ft_ftoa_printf.c \
		ft_printf_buffer.c \
		ft_printf_buffer2.c \
		ft_printf_char_str_handlers.c \
		ft_printf_convert_buffer.c \
		ft_printf_flags_parsing.c \
		ft_printf_float_handlers.c \
		ft_printf_helpers.c \
		ft_printf_hex_handlers.c \
		ft_printf_int_handlers.c \
		ft_printf_node.c \
		ft_printf_uint_handlers.c \
		ft_printf_utils.c

OBJS = $(SRCS:.c=.o)
HEADER = libft.h
SRCSBONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJSBONUS = ${SRCSBONUS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS) $(OBJSBONUS) $(HEADER)
	ar -rcs $(NAME) $(OBJS) $(OBJSBONUS)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^ 

clean:
	rm -rf $(OBJS) $(OBJSBONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

so:
	$(CC) -nostartfiles -fPIC -c $(CFLAGS) $(SRCS)
	cc -nostartfiles -shared -o libft.so $(OBJS) -ldl

breaker:
	$(CC) -nostartfiles -shared -fPIC -ldl $(CFLAGS) -o libft.so $(SRCS) $(SRCSBONUS)

.PHONY: all clean fclean re
