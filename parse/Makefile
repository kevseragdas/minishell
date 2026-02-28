NAME = parse.a
CFLAGS = 
LIBS = -lreadline

SRCS = lexer.c free_token_list.c check_token_syntax.c create_cmds.c create_redirs.c

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