# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/15 14:48:56 by blaurent          #+#    #+#              #
#    Updated: 2022/10/04 14:58:35 by blaurent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

FLAGS		= -Wall -Wextra -Werror

FILES		= main.c \
				utils.c \
				init.c \
				thread.c \
				
OBJ			= $(FILES:%.c=%.o)

all: $(OBJ) $(NAME)

$(NAME): $(OBJ)
	gcc -pthread -o $(NAME) $(OBJ)

%.o: %.c
	gcc -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re