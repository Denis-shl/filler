/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprinf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 20:12:34 by oargrave          #+#    #+#             */
/*   Updated: 2019/09/11 20:13:39 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	take_str_before_persent(char **traverse)
{
	char			*trav;

	trav = *traverse;
	while (*trav != '%' && *trav != '\0')
	{
		if (*trav == '{')
		{
			take_color(&trav);
			continue ;
		}
		ft_buffaddsymb(g_output, *trav);
		trav++;
	}
	*traverse = trav;
	if (*trav == '\0')
		return (END_OF_STRING);
	return (0);
}

static void	output(size_t *size, int fd)
{
	*size = g_output->i;
	write(fd, g_output->str, g_output->i);
}

static void	totalfree(void)
{
	ft_buffdel(&g_output);
	widthfree();
	gspecfree();
}

size_t		ft_fprintf(int fd, const char *format, va_list arg)
{
	char			*traverse;
	size_t			size;

	traverse = (char *)format;
	if (!(format))
		return (0);
	g_output = ft_buffinit(40);
	g_spec = NULL;
	while (*traverse != '\0')
	{
		init_gspec();
		init_width();
		if (take_str_before_persent(&traverse) == END_OF_STRING)
			break ;
		struct_spec(&traverse, arg);
		print_arg(arg);
	}
	output(&size, fd);
	totalfree();
	return (size);
}
