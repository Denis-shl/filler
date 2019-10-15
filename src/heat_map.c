#include "../includes/filler.h"

extern char		    **playing_field;
extern char		    **figures_field;
extern char         *player_my;
extern char         *player_en;
extern short	    **heat_map;
extern VERTICAL     map_size_y;
extern HORIZONTAL   map_size_x;

void	create_heat_map(void)
{
	un_int index;
	un_int jindex;

	index = 0;
	heat_map = (short **)malloc(map_size_y * (sizeof(short *)));
	while (index < map_size_y)
	{
		heat_map[index] = (short *)malloc(map_size_x * (sizeof(short)));
		jindex = 0;
		while (jindex < map_size_x)
		{
			if (playing_field[index][jindex] == '.')
				heat_map[index][jindex] = 0;
			else if (playing_field[index][jindex] == player_my[0]
			|| playing_field[index][jindex] == player_my[1])
				heat_map[index][jindex] = -2;
			else if ((playing_field[index][jindex] == player_en[0]
			|| playing_field[index][jindex] == player_en[1]))
				heat_map[index][jindex] = -1;
			jindex++;
		}
		index++;
	}
}

void	init_heat_map_two(int x, int y)
{
	if (x + 1 < map_size_x && heat_map[y][x + 1] == -1)
		heat_map[y][x] = 1;
	if (y + 1 < map_size_y && heat_map[y + 1][x] == -1)
		heat_map[y][x] = 1;
	if (x + 1 < map_size_x && y + 1 < map_size_y && heat_map[y + 1][x + 1] == -1)
		heat_map[y][x] = 1;
	if (x + 1 < map_size_x && y - 1 >= 0 && heat_map[y - 1][x + 1] == -1)
		heat_map[y][x] = 1;
	if (x - 1 >= 0 && heat_map[y][x - 1] == -1)
		heat_map[y][x] = 1;
	if (y - 1 >= 0 && heat_map[y - 1][x] == -1)
		heat_map[y][x] = 1;
	if (x - 1 >= 0 && y + 1 < map_size_y && heat_map[y + 1][x - 1] == -1)
		heat_map[y][x] = 1;
	if (x - 1 >= 0 && y - 1 >= 0 && heat_map[y - 1][x - 1] == -1)
		heat_map[y][x] = 1;
}

void	init_heat_map()
{
	int x;
	int y;
	int i;

	y = 0;
	i = 0;
	while (y < map_size_y)
	{
		x = 0;
		while (x < map_size_x)
		{
			if (heat_map[y][x] == 0)
			{
				init_heat_map_two(x, y);
			}
			x++;
		}
		y++;
	}
}

static int put_index_h(int x, int y, short min)
{
	if (min > heat_map[y][x] && heat_map[y][x] > 0)
		min = heat_map[y][x];
	return (min);
}

int		put_index_heat(int x, int y, int *flag)
{
	short min;

	min = 3200;
	if (x + 1 < map_size_x)
		min = put_index_h(x + 1, y, min);
	if (x - 1 >= 0)
		min = put_index_h(x - 1, y, min);
	if (x + 1 < map_size_x && y + 1 < map_size_y)
		min = put_index_h(x + 1, y + 1, min);
	if (x - 1 >= 0 && y + 1 < map_size_y)
		min = put_index_h(x - 1, y + 1, min);
	if (x - 1 >= 0 && y - 1 >= 0)
		min = put_index_h(x - 1, y - 1, min);
	if (x + 1 < map_size_x && y - 1 >= 0)
		min = put_index_h(x + 1, y - 1, min);
	if (heat_map[y][x] >= 0 && min > heat_map[y][x] && min != 3200)
	{
		heat_map[y][x] = min + 1;
		*flag = 1;
	}
	return (1);
}