# Base variables for printf library

CC = gcc
CFLAGS = -g -c
PRINTF_H = -I ../includes/
COMPILING = $(CC) $(CFLAGS) $(PRINTF_H)
NAME = libftprintf.a
EXECUTABLE = ft_printf
