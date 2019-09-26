# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/02 12:36:28 by yquaro            #+#    #+#              #
#    Updated: 2019/09/11 13:24:44 by oargrave         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include includes/printf.mk

all:
	@make -C libft/ all
	@make -C src/ all
	@make -C lib/ all
	# gcc -g main.c -I includes/ -L. lib/libftprintf.a -o ft_printf

clean:
	@make -C lib/ clean
	@make -C libft/ clean
	@make -C src/ clean

fclean: clean
	@make -C libft/ fclean
	@make -C src/ fclean
	@make -C lib/ fclean
	@rm -f $(NAME)
	@rm -f $(EXECUTABLE)

re: fclean all