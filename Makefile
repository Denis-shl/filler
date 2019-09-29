SOURCES = src/main.c src/ft_read.c src/player_access.c src/ft_free.c\
		src/search.c

OBJECTS = main.o ft_read.o player_access.o ft_free.o search.o

all:
	gcc -g  $(SOURCES) ft_printf/lib/libftprintf.a -I ft_printf/includes/header.h

clean:
	rm -rf $(OBJECTS)

fclean: clean 
	rm -rf filler