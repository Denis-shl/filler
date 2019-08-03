SOURCES = src/main.c

OBJECTS = srs/main.o

all:
	gcc -c $(SOURCES)

clean:
	rm -rf mian.o

fclean: clean 
	rm -rf ./a.out