NAME = minishell
CC = cc
CFLAGS = -g
LIBS = -lreadline

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

PARS_DIR = ./parse
PARSE = $(PARS_DIR)/parse.a

BUILTIN_DIR = ./builtin
BUILTIN = $(BUILTIN_DIR)/builtin.a

SRCS = main.c 
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(PARSE) $(BUILTIN) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)  $(PARSE) $(BUILTIN) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)
$(PARSE):
	make -C $(PARS_DIR)
$(BUILTIN):
	make -C $(BUILTIN_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(PARS_DIR) clean
	make -C $(BUILTIN_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(PARS_DIR) fclean
	make -C $(BUILTIN_DIR) fclean

re: fclean all

.PHONY: all clean fclean re