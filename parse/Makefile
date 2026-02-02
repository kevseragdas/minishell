NAME = parse.a
CFLAGS = 
LIBS = -lreadline

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = parse.c free_token_list.c check_token_syntax.c create_cmds.c create_redirs.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	ar rc $(NAME) $(CFLAGS) $(OBJS)

$(LIBFT):
	make -C $(LIBFT_DIR)


clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re