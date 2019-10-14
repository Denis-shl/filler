#include "../includes/filler.h"

extern char **playing_field;
extern char **figures_field;
extern char *player_my;
extern char *player_en;
extern un_int start_my_x;
extern un_int start_my_y;
extern un_int start_enemy_x;
extern un_int start_enemy_y;
extern VERTICAL map_size_y;
extern HORIZONTAL map_size_x;
extern short **heat_map;

void blank_field()
{
	un_int x;
	un_int y;

	g_piece.bl_f = 0;
	x = 0;
	y = 0;
	while (y < map_size_y)
	{
		x = 0;
		while (x < map_size_x)
		{
			if (heat_map[y][x] > 0)
			{
				g_piece.bl_f = 1;
				return;
			}
			x++;
		}
		y++;
	}
}

int flag_start(int *x, int *y)
{
	if (g_piece.flag == 1)
	{
		g_piece.flag = 0;
		if (((*x) + 1) < g_piece.size_x)
			(*x)++;
		else if (((*y) + 1) < g_piece.size_y)
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

int next_start(int *x, int *y)
{

	if (flag_start(x, y) == 0)
		return (0);
	if (*x == 0 && *y == 0 && figures_field[*y][*x] == '*')
	{
		g_piece.flag = 1;
		return (1);
	}
	else
	{
		while (*y < g_piece.size_y)
		{
			while (*x < g_piece.size_x)
			{
				if (figures_field[*y][*x] == '*' && figures_field)
				{
					g_piece.flag = 1;
					return (1);
				}
				(*x)++;
			}
			*x = 0;
			(*y)++;
		}
	}
	return (0);
}

int count_score(int i, int j, int *score)
{
	if (g_piece.y + j - g_piece.tempj < 0 || g_piece.y + j - g_piece.tempj >= map_size_y ||
		g_piece.x + i - g_piece.tempi < 0 || g_piece.x + i - g_piece.tempi >= map_size_x)
		return (1);
	if (heat_map[g_piece.y + j - g_piece.tempj][g_piece.x + i - g_piece.tempi] == -2 ||
		heat_map[g_piece.y + j - g_piece.tempj][g_piece.x + i - g_piece.tempi] == -1)
	{
		if (i != g_piece.tempi || j != g_piece.tempj)
			return (1);
	}
	if (heat_map[g_piece.y + j - g_piece.tempj][g_piece.x + i - g_piece.tempi] != -2)
		*score += heat_map[g_piece.y + j - g_piece.tempj][g_piece.x + i - g_piece.tempi];
	return (0);
}

int c_before(int x, int y, int *score)
{
	g_piece.tempi = x;
	g_piece.tempj = y;

	while (y >= 0)
	{
		while (x >= 0)
		{
			if (figures_field[y][x] == '*')
			{
				if (count_score(x, y, score) == 1)
					return (1);
			}
			x--;
		}
		x = g_piece.size_x - 1;
		y--;
	}
	return (0);
}

int c_after(int x, int y, int *score)
{
	g_piece.tempi = x;
	g_piece.tempj = y;

	while (y < g_piece.size_y)
	{
		while (x < g_piece.size_x)
		{
			if (figures_field[y][x] == '*')
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

void get_score(int score)
{
	if (g_piece.bl_f == 1)
	{
		if ((score <= g_piece.score && score > 0) || (score > 0 && g_piece.score == 0))
		{
			g_piece.score = score;
			g_piece.tmp_x = g_piece.x - g_piece.i;
			g_piece.tmp_y = g_piece.y - g_piece.j;
		}
		else
		{
			g_piece.score2 = score;
			g_piece.tmp_x2 = g_piece.x - g_piece.i;
			g_piece.tmp_y2 = g_piece.y - g_piece.j;
		}
	}
	else
	{
		if (score < g_piece.score || g_piece.score == 0)
		{
			g_piece.score = score;
			g_piece.score2 = score;
			g_piece.tmp_x2 = g_piece.x - g_piece.i;
			g_piece.tmp_y2 = g_piece.y - g_piece.j;
		}
	}
}

void algol(int x, int y)
{
	int score;
	int index;

	g_piece.i = 0;
	g_piece.j = 0;
	index = 0;	
	while ((next_start(&g_piece.i , &g_piece.j) == 1))
	{
		score = 0;
		g_piece.start_x = g_piece.i;
		g_piece.start_y = g_piece.j;
		if ((c_before(g_piece.i, g_piece.j, &score)) == 0
			&& (c_after(g_piece.i, g_piece.j, &score) == 0))
		{
			get_score(score);
		}
		index++;
	}
	if (g_piece.score == 0)
	{
		g_piece.score = g_piece.score2;
		g_piece.tmp_x = g_piece.tmp_x2;
		g_piece.tmp_y = g_piece.tmp_y2;
	}
}

int	finding_place_for_figure()
{
	g_piece.x = 0;
	g_piece.y = 0;

	blank_field();
	while (g_piece.y < map_size_y)
	{
		g_piece.x = 0;
		while (g_piece.x < map_size_x)
		{
			if (heat_map[g_piece.y][g_piece.x] == -2)
			{
				algol(g_piece.x, g_piece.y);
			}
			g_piece.x++;
		}
		g_piece.y++;
	}
	return (1);
}