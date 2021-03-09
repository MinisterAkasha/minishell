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
INCLUDE = ./Includes
LIBFT = ./src/utils/libft/libft.a
C_FILES = main.c get_next_line.c
OBJDIR = ./src/obj
OBJ = $(C_FILES:%.c=%.o)
OFILES = $(addprefix $(OBJDIR)/, $(OBJ))

vpath %.c ./src/utils/GNL ./src/utils ./src
vpath %.o $(OBJDIR)
vpath %.h $(INCLUDE)

.PHONY: all clean fclean re libft

all: $(OBJDIR) libft $(NAME)

libft:
	make -C ./src/utils/libft/

$(NAME): $(OBJ)
	$(CC) -I$(INCLUDE) $(LIBFT) $(OFILES) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

%.o: %.c
	echo "Creating objects"
	$(CC) -I$(INCLUDE) -c $^ -o $(OBJDIR)/$@

clean:
	rm -rf $(OBJDIR)


