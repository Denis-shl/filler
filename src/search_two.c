/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:22:26 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/16 12:03:41 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

extern char			**g_map;
extern char			**g_fmap;

int		flag_start(int *x, int *y)
{
	if (g_pi.flag == 1)
	{
		g_pi.flag = 0;
		if (((*x) + 1) < g_pi.size_x)
			(*x)++;
		else if (((*y) + 1) < g_pi.size_y)
		{
			*x = 0;
			(*y)++;
		}
		else
		{
			return (0);
		}
	}
	return (1);
}

int		next_start(int *x, int *y)
{
	if (flag_start(x, y) == 0)
		return (0);
	if (*x == 0 && *y == 0 && g_fmap[*y][*x] == '*')
	{
		g_pi.flag = 1;
		return (1);
	}
	else
		while (*y < g_pi.size_y)
		{
			while (*x < g_pi.size_x)
			{
				if (g_fmap[*y][*x] == '*' && g_fmap)
				{
					g_pi.flag = 1;
					return (1);
				}
				(*x)++;
			}
			*x = 0;
			(*y)++;
		}
	return (0);
}

void	get_score(int score)
{
	if (g_pi.bl_f == 1)
	{
		if ((score <= g_pi.score && score > 0)
				|| (score > 0 && g_pi.score == 0))
		{
			g_pi.score = score;
			g_pi.tmp_x = g_pi.x - g_pi.i;
			g_pi.tmp_y = g_pi.y - g_pi.j;
		}
		else
		{
			g_pi.score2 = score;
			g_pi.tmp_x2 = g_pi.x - g_pi.i;
			g_pi.tmp_y2 = g_pi.y - g_pi.j;
		}
	}
	else if (score < g_pi.score || g_pi.score == 0)
	{
		g_pi.score = score;
		g_pi.score2 = score;
		g_pi.tmp_x2 = g_pi.x - g_pi.i;
		g_pi.tmp_y2 = g_pi.y - g_pi.j;
	}
}

void	algol(int x, int y)
{
	int			score;
	int			index;

	g_pi.i = 0;
	g_pi.j = 0;
	index = 0;
	while ((next_start(&g_pi.i, &g_pi.j) == 1))
	{
		score = 0;
		if ((c_before(g_pi.i, g_pi.j, &score)) == 0
			&& (c_after(g_pi.i, g_pi.j, &score) == 0))
		{
			get_score(score);
		}
		index++;
	}
	if (g_pi.score == 0)
	{
		g_pi.score = g_pi.score2;
		g_pi.tmp_x = g_pi.tmp_x2;
		g_pi.tmp_y = g_pi.tmp_y2;
	}
}
