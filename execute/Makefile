NAME = execute.a
CFLAGS = 
LIBS = 

SRCS = 

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