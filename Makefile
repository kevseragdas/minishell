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

EXEC_DIR = ./execute
EXEC = $(EXEC_DIR)/execute.a

SRCS = main.c signal.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(PARSE) $(EXEC) $(BUILTIN) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)  $(PARSE) $(EXEC) $(BUILTIN) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)
$(PARSE):
	make -C $(PARS_DIR)
$(BUILTIN):
	make -C $(BUILTIN_DIR)
$(EXEC):
	make -C $(EXEC_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(PARS_DIR) clean
	make -C $(BUILTIN_DIR) clean
	make -C $(EXEC_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(PARS_DIR) fclean
	make -C $(BUILTIN_DIR) fclean
	make -C $(EXEC_DIR) fclean

re: fclean all

.PHONY: all clean fclean re