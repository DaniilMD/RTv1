# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: openelop <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/31 13:23:41 by openelop          #+#    #+#              #
#    Updated: 2019/12/31 13:23:45 by openelop         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC = main.c parser.c vector_operations.c trace_ray.c intersecters.c lighting.c \
	help_functions.c

OBJ = $(SRC:.c=.o)

HEADER = rtv1.h

##FLAGS = -Wall -Wextra -Werror

FLAGS =  

MLX_FLAGS = -L ./mlx/ -lmlx -framework OpenGL -framework AppKit

$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(FLAGS) $(SRC) -o $(NAME) -L libft -lft $(MLX_FLAGS)

%.o:%.c $(HEADER)
	@gcc $(FLAGS) -I . -c $< -o $@

clean:
	@/bin/rm -f *~
	@/bin/rm -f $(OBJ)
	@make -C libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean

all: $(NAME)

re: fclean all

.PHONY: clean fclean all re
