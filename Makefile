NAME = ircserv

CC = c++
RM = rm -rf
CFLAGS = -Wall -g -Werror -Wextra -std=c++98 #-fsanitize=address

#directories
SRC_DIR		=	src/
OBJ_DIR		=	.obj/
INC_DIR		=	includes/

#color codes
GREEN 	= \033[1;32m
END 	= \033[0m

#source files
SRCS =  main \
		Server \
		Client \
		Channel \
		IRCCommandHandler \
		commands/join \
		commands/nick \
		commands/topic \
		commands/kick \
		commands/invite \
		commands/mode \
		commands/privmsg \
		commands/pass \
		commands/user 


OBJS = $(SRCS:.cpp=.o)

#paths
SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRCS)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRCS)))
all: $(NAME)

#executable compilation
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\n$(GREEN)¡Compilation Success, you can run ft_irc!$(END)\n"

#objs compilation
$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/commands
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: $(NAME)
	@./$(NAME)
	
.PHONY: all clean fclean re run
