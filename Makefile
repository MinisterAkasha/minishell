# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tilda <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/09 14:03:17 by tilda             #+#    #+#              #
#    Updated: 2021/03/09 14:03:19 by tilda            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
INCLUDE = -I ./Includes
LIBFT = ./src/utils/libft/libft.a
#exlude libft -> -path ./src/utils/libft -prune -false -o
C_FILES = $(shell find . -path ./src/utils/libft -prune -false -o -name "*.c")

.PHONY: all clean fclean re libft

all: libft $(NAME)

libft:
	make -C ./src/utils/libft/

$(NAME):
	$(CC) $(INCLUDE) $(LIBFT) $(C_FILES)
