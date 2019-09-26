/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 20:32:44 by yquaro            #+#    #+#             */
/*   Updated: 2019/09/11 13:18:16 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char				*parsesymb(char *traverse, va_list arg)
{
	if (is_badsymb(*traverse))
		return (traverse);
	else if (*traverse == ' ')
		traverse = parse_spaces(traverse, arg);
	else if (*traverse == '.')
		traverse = parse_width_or_precision(traverse, PRECISION, arg);
	else if (is_calculatesymb(*traverse))
		traverse = parse_calculatesymb(traverse, arg);
	else if (ft_isdigit(*traverse) || (*traverse == ASTERISC))
		traverse = parse_width_or_precision(traverse, WIDTH, arg);
	else if (is_lh_bigl(*traverse))
		traverse = parse_lh_bigl(traverse, arg);
	else if (*traverse == 'j')
	{
		g_spec->j = 1;
		traverse = parsesymb(++traverse, arg);
	}
	else if (*traverse == 'z')
	{
		g_spec->z = 1;
		traverse = parsesymb(++traverse, arg);
	}
	if (g_spec->minus == 1)
		g_spec->zero = 0;
	return (traverse);
}

static void			lowercase(void)
{
	if (g_spec->symb == 'O')
	{
		g_spec->l = 1;
		g_spec->symb = 'o';
	}
	else if (g_spec->symb == 'S')
	{
		g_spec->l = 1;
		g_spec->symb = 's';
	}
	else if (g_spec->symb == 'C')
		g_spec->symb = 'c';
	else if (g_spec->symb == 'Z')
		g_spec->symb = 'z';
	else if (g_spec->symb == 'D')
	{
		g_spec->l = 1;
		g_spec->symb = 'd';
	}
	else if (g_spec->symb == 'F')
	{
		g_spec->l = 1;
		g_spec->symb = 'f';
	}
}

void				struct_spec(char **traverse, va_list arg)
{
	char			*trav;

	trav = *traverse + 1;
	if (is_badsymb(*trav))
	{
		if (is_specifier(*trav))
		{
			g_spec->symb = *trav;
			lowercase();
			*traverse = trav + 1;
			return ;
		}
		*traverse = trav;
		return ;
	}
	else
		trav = parsesymb(trav, arg);
	if (is_specifier(*trav))
	{
		g_spec->symb = *trav;
		lowercase();
		trav++;
	}
	*traverse = trav;
}

char				*parse_spaces(char *traverse, va_list arg)
{
	g_spec->space = 1;
	while (*traverse == ' ')
		traverse++;
	traverse = parsesymb(traverse, arg);
	if (g_spec->symb == 'i')
		g_spec->symb = 'd';
	return (traverse);
}

char				*parse_aster(char *traverse, const int flag,
	va_list arg)
{
	int value;

	value = 0;
	if (*traverse != ASTERISC)
		return (traverse);
	value = va_arg(arg, int);
	if (flag == WIDTH)
		g_spec->width = value;
	else if (flag == PRECISION)
		g_spec->precision = value;
	return (traverse + 1);
}
