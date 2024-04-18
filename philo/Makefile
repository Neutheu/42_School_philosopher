# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 09:14:12 by nsouchal          #+#    #+#              #
#    Updated: 2024/04/18 11:09:44 by nsouchal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_FILE = main.c

DIR_BUILD		=	.build/
DIR_SRCS 		= 	srcs/
DIR_HEADERS		=	includes/

HEADERFILES		=	$(DIR_HEADERS)philo.h

OBJS			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRCS))
SRCS			=	$(addprefix $(DIR_SRCS),$(SRC_FILE))

FLAGS		=	-Wall -Werror -Wextra -pthread

CC = cc

.PHONY: all
all: libft $(NAME)

$(NAME): $(OBJS)
			$(CC) $(OBJS) -o $(NAME)

$(DIR_BUILD)%.o: %.c $(HEADERFILES) Makefile
				mkdir -p $(shell dirname $@)
				$(CC) $(FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(DIR_BUILD)

.PHONY: fclean
fclean: clean
		rm -rf $(NAME)

.PHONY: re
re: fclean
	$(MAKE) all
