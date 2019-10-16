# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 11:18:41 by oargrave          #+#    #+#              #
#    Updated: 2019/10/16 12:56:41 by oargrave         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = oargrave.filler
SOURCES = src/main.c src/ft_read.c src/player_access.c src/ft_free.c\
		src/search.c  src/heat_map.c src/search_two.c

OBJECTS = main.o ft_read.o player_access.o ft_free.o search.o heat_map.o\
		search_two.0

all: $(NAME)
$(NAME):
	make -C ft_printf/ all
	gcc -g  $(SOURCES) ft_printf/lib/libftprintf.a -I ft_printf/includes/ -o $(NAME)

clean:
	make -C ft_printf/ clean
	rm -rf $(OBJECTS)

fclean: clean
	make -C ft_printf/ fclean
	rm -rf $(NAME)
re: fclean all
