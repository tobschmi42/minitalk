CC=cc
CFLAGS=-Wextra -Wall -Werror

SRCS_HELPER = helper.c
OBJS_HELPER = $(SRCS_HELPER:.c=.o)
SRCS_CLIENT = client.c $(SRCS_HELPER)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
SRCS_SERVER = server.c $(SRCS_HELPER)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

NAME_CLIENT = client
NAME_SERVER = server

LIBFT = ./libft/libft.a

all: $(LIBFT) $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT) -o $(NAME_SERVER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: re fclean clean all
