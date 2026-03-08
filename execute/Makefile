NAME = execute.a
CFLAGS = 
LIBS = 

SRCS = exec_builtin.c exec_external_helper.c exec_external.c execute_non_single.c \
		execute_single.c execute.c redirections.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):  $(OBJS)
	ar rc $(NAME) $(CFLAGS) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re