/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_next_star.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 19:20:44 by mdubus            #+#    #+#             */
/*   Updated: 2019/10/10 16:35:30 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static int	flag_star(t_filler *f, int *i, int *j)
{
	if (f->flag_star == 1)
	{
		f->flag_star = 0;
		if (*i + 1 < f->w_piece)
			(*i)++;
		else if (*j + 1 < f->h_piece)
		{
			*i = 0;
			(*j)++;
		}
		else
		{
			printf ("else\n");
			return (0);
		}
	}
	return (1);
}

int			search_next_star(t_filler *f, int *i, int *j)
{

	printf ("x = %d\n", f->w_piece);
	printf ("y = %d\n", f->h_piece);
	
	if (flag_star(f, i, j) == 0)
		return (0);
	if (*i == 0 && *j == 0 && f->piece && f->piece[*j][*i] == '*')
	{
		f->flag_star = 1;
		return (1);
	}
	else
	{
		while (*j < f->h_piece)
		{
			while (*i < f->w_piece)
			{
				if (f->piece && f->piece[*j][*i] == '*')
				{
					f->flag_star = 1;
					return (1);
				}
				(*i)++;
			}
			*i = 0;
			(*j)++;
		}
	}
	return (0);
}
