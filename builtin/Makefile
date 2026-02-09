NAME = builtin.a
CFLAGS =

SRCS = builtin_functions.c get_envp.c pwd.c echo.c env.c exit.c cd.c unset.c export.c expander.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(CFLAGS) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re