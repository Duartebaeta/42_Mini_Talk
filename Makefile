NAME := minitalk
CC := gcc
CFLAGS := -Wall -Wextra -Werror

PATH_SRC := ./src
PATH_SERVER := $(PATH_SRC)/server.c
PATH_CLIENT := $(PATH_SRC)/client.c
PATH_LIBFT := ./libft
PATH_INCLUDES := ./includes

SERVER := ./server
CLIENT := ./client

LIBFT := $(PATH_LIBFT)/libft.a

all:$(SERVER) $(CLIENT)

$(SERVER): $(LIBFT)
		@$(CC) $(CFLAGS) -o $(@) $(PATH_SERVER) -L$(PATH_LIBFT) -lft -I$(PATH_INCLUDES)
		@echo "\033[33m[Compiling SERVER]\033[0m"

$(CLIENT): $(LIBFT)
		@$(CC) $(CFLAGS) -o $(@) $(PATH_CLIENT) -L$(PATH_LIBFT) -lft -I$(PATH_INCLUDES)
		@echo "\033[33m[Compiling SERVER]\033[0m"

$(LIBFT):
		@make -C $(PATH_LIBFT)

clean:
		@echo "\033[38;5;1m[REMOVING OBJECTS]\033[0m"
		@rm -rf $(SERVER) $(CLIENT)

fclean: clean
		@echo "\033[38;5;1m[REMOVING BINARIES]\033[0m"
		@rm -rf $(SERVER) $(CLIENT)
		@make fclean -C $(PATH_LIBFT)

exe: all
		@./$(NAME)

re: fclean all

.PHONY: all exe