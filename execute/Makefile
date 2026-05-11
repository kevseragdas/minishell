NAME = execute.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = exec_builtin.c exec_external_helper.c exec_external.c execute_non_single.c \
       execute_single.c execute_non_single_helper1.c execute_non_single_helper2.c \
       execute.c redirections.c heredoc.c

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