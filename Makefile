# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/05 10:58:02 by tkuhar            #+#    #+#              #
#    Updated: 2018/05/12 17:49:17 by tkuhar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_OFF=\033[0m#			# Text Reset
BLACK	=\033[0;30m#		# Black
RED		=\033[0;31m#		# Red
GREEN	=\033[0;32m#		# Green
YELLOW	=\033[0;33m#		# Yellow
BLUE	=\033[0;34m#		# Blue
PURPLE	=\033[0;35m#		# Purple
CYAN	=\033[0;36m#		# Cyan
WHITE	=\033[0;37m#		# White

CC= gcc
FLAGS= -Wall -Wextra -Werror
NAME= libftprintf.a
SRC= flags_processing.c \
ft_getcharw.c \
ft_getstrw.c \
ft_itoa_base.c \
ft_printf.c \
ft_strinsert.c \
func_call.c \
func_print.c
OBJ= $(SRC:%.c=%.o)


OK_STRING    =***	$(NAME) created		***

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C ./libft
	@ar rcs $(NAME) $(OBJ) ./libft/*.o
	@printf "\n$(GREEN)$(OK_STRING)\n\n"
%.o:%.c
	@$(CC) $(FLAGS) -c $< -o $@ 
	@printf "$(CYAN)compiling $<$(COLOR_OFF)\n"
clean:
	@rm -f $(OBJ)
	@$(MAKE) clean -C ./libft
	@printf  "$(YELLOW)remove OBJ"
fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@$(MAKE) fclean -C ./libft
	@printf "$(YELLOW)remove OBJ$(COLOR_OFF)\n"
	@printf "$(RED)remove $(NAME)$(COLOR_OFF)\n"

re: fclean all