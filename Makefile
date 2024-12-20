NAME = ircserv

CC = c++
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -std=c++98 #-fsanitize=address

#directories
SRC_DIR		=	src/
OBJ_DIR		=	.obj/
INC_DIR		=	includes/

#color codes
GREEN = \033[1;32m
END = \033[0m

#source files
SRCS =  main.cpp \
		Server.cpp \
		Client.cpp \
		Parser.cpp \
		Channel.cpp \
		User.cpp \
		IRCCommandHandler.cpp \


OBJS = $(SRCS:.cpp=.o)

#paths
SRC			=	$(addprefix $(SRC_DIR), $(SRCS))
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJS))
all: $(NAME)

#executable compilation
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 
	@echo "\n$(GREEN)¡Compilation Success, you can run ft_irc!$(END)\n"

#objs compilation
$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: $(NAME)
	@./$(NAME)
	
.PHONY: all clean fclean re run
