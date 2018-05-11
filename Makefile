# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/05 10:58:02 by tkuhar            #+#    #+#              #
#    Updated: 2018/05/11 16:33:37 by tkuhar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
FLAGS= -Wall -Wextra -Werror
NAME= libftprintf.a
SRC= ft_printf.c ft_getcharw.c ft_getstrw.c ft_itoa_base.c
OBJ= $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C ./libft
	@ar rcs $(NAME) $(OBJ) ./libft/*.o
	@echo "#####################DONE##################\\n"

%.o:%.c
	@$(CC) $(FLAGS) -c $< -o $@ -g
	
clean:
	@rm -f $(OBJ)
	@$(MAKE) clean -C ./libft
	@echo "remove OBJ"
fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@$(MAKE) fclean -C ./libft
	@echo "remove OBJ"
	@echo "remove $(NAME)"

re: fclean all