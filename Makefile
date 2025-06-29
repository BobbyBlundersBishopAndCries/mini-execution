CC     = cc
CFLAGS = -Wall -Werror -Wextra -g 
LDFLAGS = -lreadline -lncurses

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

D_TOK = lexical_analyser 
D_SYN = syntax_error 

SRCS = main.c \
		 builtins/ft_env.c builtins/ft_echo.c builtins/ft_cd.c builtins/ft_pwd.c builtins/ft_export.c

OBJS = $(SRCS:.c=.o)

NAME = shellax

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) > /dev/null

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
