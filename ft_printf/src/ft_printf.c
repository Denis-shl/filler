/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 15:58:05 by oargrave          #+#    #+#             */
/*   Updated: 2019/09/11 20:14:45 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

size_t		ft_printf(const char *format, ...)
{
	va_list		arg;
	size_t		size;

	size = 0;
	va_start(arg, (char *)format);
	size = ft_fprintf(1, format, arg);
	va_end(arg);
	return (size);
}

size_t		ft_vprintf(int fd, const char *format, ...)
{
	size_t	size;
	va_list	arg;

	size = 0;
	va_start(arg, (char *)format);
	size = ft_fprintf(fd, format, arg);
	va_end(arg);
	return (size);
}
