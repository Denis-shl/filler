/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:18:55 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/16 12:19:05 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

extern char			**g_map;
extern char			**g_fmap;
extern char			*g_play_my;
extern char			*g_play_en;
extern int		g_size_y;
extern int	g_size_x;
extern short		**g_hmap;

void	blank_field(void)
{
	int		x;
	int		y;

	g_pi.bl_f = 0;
	x = 0;
	y = 0;
	while (y < g_size_y)
	{
		x = 0;
		while (x < g_size_x)
		{
			if (g_hmap[y][x] > 0)
			{
				g_pi.bl_f = 1;
				return ;
			}
			x++;
		}
		y++;
	}
}

int		count_score(int i, int j, int *score)
{
	if (g_pi.y + j - g_pi.tempj < 0 ||
	g_pi.y + j - g_pi.tempj >= g_size_y ||
		g_pi.x + i - g_pi.tempi < 0 ||
		g_pi.x + i - g_pi.tempi >= g_size_x)
		return (1);
	if (g_hmap[g_pi.y + j - g_pi.tempj][g_pi.x + i - g_pi.tempi] == -2 ||
		g_hmap[g_pi.y + j - g_pi.tempj][g_pi.x + i - g_pi.tempi] == -1)
	{
		if (i != g_pi.tempi || j != g_pi.tempj)
			return (1);
	}
	if (g_hmap[g_pi.y + j - g_pi.tempj][g_pi.x + i - g_pi.tempi] != -2)
		*score += g_hmap[g_pi.y + j - g_pi.tempj][g_pi.x + i - g_pi.tempi];
	return (0);
}

int		c_before(int x, int y, int *score)
{
	g_pi.tempi = x;
	g_pi.tempj = y;
	while (y >= 0)
	{
		while (x >= 0)
		{
			if (g_fmap[y][x] == '*')
			{
				if (count_score(x, y, score) == 1)
					return (1);
			}
			x--;
		}
		x = g_pi.size_x - 1;
		y--;
	}
	return (0);
}

int		c_after(int x, int y, int *score)
{
	g_pi.tempi = x;
	g_pi.tempj = y;
	while (y < g_pi.size_y)
	{
		while (x < g_pi.size_x)
		{
			if (g_fmap[y][x] == '*')
			{
				if (count_score(x, y, score) == 1)
					return (1);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int		finding_place_for_figure(void)
{
	g_pi.x = 0;
	g_pi.y = 0;
	g_pi.score = 0;
	g_pi.score2 = 0;
	g_pi.tmp_x = 0;
	g_pi.tmp_y = 0;
	g_pi.tmp_x2 = 0;
	g_pi.tmp_y2 = 0;
	blank_field();
	while (g_pi.y < g_size_y)
	{
		g_pi.x = 0;
		while (g_pi.x < g_size_x)
		{
			if (g_hmap[g_pi.y][g_pi.x] == -2)
			{
				algol(g_pi.x, g_pi.y);
			}
			g_pi.x++;
		}
		g_pi.y++;
	}
	return (1);
}
