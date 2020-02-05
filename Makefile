# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/06 22:26:44 by aguiller          #+#    #+#              #
#    Updated: 2020/01/31 18:50:55 by alexzudin        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c get_next_line.c validation.c algos.c draw_line.c init.c

NAME = fdf

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) 
	@cd libft && $(MAKE) all
	@cd miniLibX && $(MAKE) all
	@gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) -L./libft -lft \
	-L./miniLibX -lmlx -framework OpenGL -framework AppKit

%.o:%.c
	@gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	@cd libft && $(MAKE) clean	
	@cd miniLibX && $(MAKE) clean
	@/bin/rm -f $(OBJ)

fclean: clean
	@cd libft && $(MAKE) fclean
	@/bin/rm -f $(NAME)

re: fclean  all 

