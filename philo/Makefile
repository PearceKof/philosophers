# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/15 14:48:56 by blaurent          #+#    #+#              #
#    Updated: 2022/10/11 18:30:22 by blaurent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

FLAGS		= -Wall -Wextra -Werror -pthread

FILES		= main.c \
				utils.c \
				init.c \
				thread.c \
				action.c \
				exit.c \
				
OBJ			= $(FILES:%.c=%.o)

all: $(OBJ) $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re