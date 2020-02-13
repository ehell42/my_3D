# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehell <ehell@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/06 22:26:44 by aguiller          #+#    #+#              #
#    Updated: 2020/02/06 11:43:58 by ehell            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c get_next_line.c validation.c algos.c draw_line.c init.c controls.c functions.c

NAME = fdf

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) 
	@cd libft && $(MAKE) all
	@cd minilibx_macos && $(MAKE) all
	@gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) -L./libft -lft \
	-L./minilibx_macos -lmlx -framework OpenGL -framework AppKit

%.o:%.c
	@gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	@cd libft && $(MAKE) clean	
	@cd minilibx_macos && $(MAKE) clean
	@/bin/rm -f $(OBJ)

fclean: clean
	@cd libft && $(MAKE) fclean
	@/bin/rm -f $(NAME)

re: fclean  all 

