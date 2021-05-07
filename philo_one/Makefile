# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/07 12:43:35 by asaadi            #+#    #+#              #
#    Updated: 2021/05/07 15:56:22 by asaadi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one.a

# NAME_BONUS = 

FLAGS = -Wall -Wextra -Werror

SRC_PATH = srcs

SRC_NAME = 	main.c







HDR_PATH = headers/
HDR_INC = -I ./headers
HDR_NAME = 

OBJ_PATH= objs
OBJ_NAME = $(SRC_NAME:.c=.o)

# LIBFT_PATH = ./libft

OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))

all: $(NAME) 

$(NAME): $(OBJ)

	@gcc $(FLAGS) $(OBJ) -o $(NAME)
	@echo "\033[0;33m"
	@echo "			COMPILATION DONE!\n"
	@echo "\033[0m"
	@echo "						Created by:"
	@echo "\033[1;30m"
	@echo "						  asaadi  < asaadi@student.1337.ma >\n"
	@echo "\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HDR)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@gcc $(FLAGS) $(HDR_INC)  -o $@ -c $<



# bonus: $(NAME_BONUS)

# $(NAME_BONUS): $(OBJ)
# 	@make -sC $(LIBFT_PATH)
# 	@cp libft/libft.a .
# 	@gcc $(FLAGS) libft.a $(OBJ) -o $(NAME_BONUS)
# 	@echo "\033[0;33m"
# 	@echo "			COMPILATION DONE!\n"
# 	@echo "\033[0m"
# 	@echo "						Created by:"
# 	@echo "\033[1;30m"
# 	@echo "						  abdel-mak && asaadi\n"
# 	@echo "\033[0m"

clean:
	@rm -rf $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@make clean -sC $(LIBFT_PATH)
	@echo "minishell : Removing Objs"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)
	@rm -rf libft.a
	@make fclean -sC $(LIBFT_PATH)
	@echo "minishell : Removing minishell"

re: fclean all
