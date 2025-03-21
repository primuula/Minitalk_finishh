NAME_SERVER	= server
NAME_CLIENT	= client 
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
SRCS		= server.c client.c utils.c
INC			= minitalk.h
OBJ			= $(SRCS:.c=.o)

all : $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER) : server.c utils.c
		cc -g3 $(CFLAGS) $^ -o $@
$(NAME_CLIENT) : client.c utils.c
		cc -g3 $(CFLAGS) $^ -o $@
clean:
		rm -rf $(NAME_SERVER) $(NAME_CLIENT)
fclean:
		rm -rf $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

.PHONY: all clean fclean re