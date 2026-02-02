NAME = minishell
CC = cc
CFLAGS = -g
LIBS = -lreadline

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = main.c parse.c free_token_list.c check_token_syntax.c create_cmds.c create_redirs.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re