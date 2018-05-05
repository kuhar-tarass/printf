# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/05 10:58:02 by tkuhar            #+#    #+#              #
#    Updated: 2018/05/05 12:56:09 by tkuhar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
FLAGS= -Wall -Wextra -Werror
NAME= libftprintf.a
SRC= ft_printf.c ft_putcharW.c ft_putstrW.c ft_itoa_base.c
OBJ= $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C ./libft
	@ar rcs $(NAME) $(OBJ) ./libft/*.o
	@echo "#####################DONE##################\\n"
%.o:%.c
	@$(CC) $(FLAGS) -c $< -o $@
	
clean:
	@rm -f $(OBJ)
#	@echo "remove OBJ"
fclean: clean
	@rm -f $(NAME)
#	@echo "remove $(NAME)"

re: fclean all