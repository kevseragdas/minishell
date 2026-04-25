NAME = builtin.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = builtin_functions.c get_envp.c pwd.c echo.c env.c exit.c cd.c unset.c \
        export.c export_helper.c expander.c expander_helper.c get_arr_env.c ft_atol.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re