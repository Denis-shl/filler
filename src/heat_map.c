/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:18:49 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/16 12:19:05 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

extern char			**g_map;
extern char			**g_fmap;
extern char			*g_play_my;
extern char			*g_play_en;
extern short		**g_hmap;
extern int		g_size_y;
extern int	g_size_x;

void		create_heat_map(void)
{
	int			index;
	int			jindex;

	index = 0;
	g_hmap = (short **)malloc(g_size_y * (sizeof(short *)));
	while (index < g_size_y)
	{
		g_hmap[index] = (short *)malloc(g_size_x * (sizeof(short)));
		jindex = 0;
		while (jindex < g_size_x)
		{
			if (g_map[index][jindex] == '.')
				g_hmap[index][jindex] = 0;
			else if (g_map[index][jindex] == g_play_my[0]
			|| g_map[index][jindex] == g_play_my[1])
				g_hmap[index][jindex] = -2;
			else if ((g_map[index][jindex] == g_play_en[0]
			|| g_map[index][jindex] == g_play_en[1]))
				g_hmap[index][jindex] = -1;
			jindex++;
		}
		index++;
	}
}

void		init_heat_map_two(int x, int y)
{
	if (x + 1 < g_size_x && g_hmap[y][x + 1] == -1)
		g_hmap[y][x] = 1;
	if (y + 1 < g_size_y && g_hmap[y + 1][x] == -1)
		g_hmap[y][x] = 1;
	if (x + 1 < g_size_x && y + 1 < g_size_y && g_hmap[y + 1][x + 1] == -1)
		g_hmap[y][x] = 1;
	if (x + 1 < g_size_x && y - 1 >= 0 && g_hmap[y - 1][x + 1] == -1)
		g_hmap[y][x] = 1;
	if (x - 1 >= 0 && g_hmap[y][x - 1] == -1)
		g_hmap[y][x] = 1;
	if (y - 1 >= 0 && g_hmap[y - 1][x] == -1)
		g_hmap[y][x] = 1;
	if (x - 1 >= 0 && y + 1 < g_size_y && g_hmap[y + 1][x - 1] == -1)
		g_hmap[y][x] = 1;
	if (x - 1 >= 0 && y - 1 >= 0 && g_hmap[y - 1][x - 1] == -1)
		g_hmap[y][x] = 1;
}

void		init_heat_map(void)
{
	int			x;
	int			y;
	int			i;

	y = 0;
	i = 0;
	while (y < g_size_y)
	{
		x = 0;
		while (x < g_size_x)
		{
			if (g_hmap[y][x] == 0)
			{
				init_heat_map_two(x, y);
			}
			x++;
		}
		y++;
	}
}

static int	put_index_h(int x, int y, short min)
{
	if (min > g_hmap[y][x] && g_hmap[y][x] > 0)
		min = g_hmap[y][x];
	return (min);
}

int			put_index_heat(int x, int y, int *flag)
{
	short		min;

	min = 3200;
	if (x + 1 < g_size_x)
		min = put_index_h(x + 1, y, min);
	if (x - 1 >= 0)
		min = put_index_h(x - 1, y, min);
	if (x + 1 < g_size_x && y + 1 < g_size_y)
		min = put_index_h(x + 1, y + 1, min);
	if (x - 1 >= 0 && y + 1 < g_size_y)
		min = put_index_h(x - 1, y + 1, min);
	if (x - 1 >= 0 && y - 1 >= 0)
		min = put_index_h(x - 1, y - 1, min);
	if (x + 1 < g_size_x && y - 1 >= 0)
		min = put_index_h(x + 1, y - 1, min);
	if (g_hmap[y][x] >= 0 && min > g_hmap[y][x] && min != 3200)
	{
		g_hmap[y][x] = min + 1;
		*flag = 1;
	}
	return (1);
}
