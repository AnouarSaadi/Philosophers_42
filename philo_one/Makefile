# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/07 12:43:35 by asaadi            #+#    #+#              #
#    Updated: 2021/05/18 12:38:33 by asaadi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

FLAGS = -Wall -Wextra -Werror

SRC_PATH = srcs

SRC_NAME = 	main.c







HDR_PATH = headers/
HDR_INC = -I ./headers
HDR_NAME = 

OBJ_PATH= objs
OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))

all: $(NAME) 

$(NAME): $(OBJ)
	@echo "\033[1;93m"
	@echo "		THE PHILOSOPHERS"
	@echo "\033[0m"
	@echo "				Philo_one"
	@gcc $(FLAGS) $(OBJ) -o $(NAME)
	@echo "\033[0;33m"
	@echo "				Compilation: Done!"
	@echo "\033[0m"
	@echo "\033[1;30m"
	@echo "				asaadi  <asaadi@student.1337.ma> <https://github.com/a-saadi>"
	@echo "\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HDR)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@gcc $(FLAGS) -pthread $(HDR_INC)  -o $@ -c $<

clean:
	@rm -rf $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[1;91m"
	@echo "				minishell : Removing Objs"
	@echo "\033[0m"


fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;91m"
	@echo "				minishell : Removing minishell"
	@echo "\033[0m"


re: fclean all
