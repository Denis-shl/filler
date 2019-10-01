
#include "../includes/filler.h"

char		**playing_field = NULL;
char		**figures_field = NULL;
extern char	*player_my;
extern char *player_en;
VERTICAL	map_size_y;
HORIZONTAL	map_size_x;
un_int		start_my_x = 0;
un_int		start_my_y = 0;
un_int		start_enemy_x = 0;
un_int		start_enemy_y = 0;
short		**heat_map = NULL;

int		ft_lennumb(int num)
{
	int		len;

	len = 0;
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static void	create_heat_map(void)
{
	un_int index;
	un_int jindex;

	index = 0;
	jindex = 0;
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

void	put_index()
{
	int x;
	int y;
	int flag;
	int min;

	flag = 1;
	while (flag == 1)
	{
		y = 0;
		flag = 0;
		while (y < map_size_y)
		{
			x = 0;
			while (x < map_size_x)
			{
				put_index_heat(x, y, &flag);
				x++;
			}
			y++;
		}
	}
}

void	ft_record_map(VERTICAL y)
{
	int		status_read;
	un_int	index;
	char	*str;

	status_read = 0;
	str = NULL;
	index = 0;
	get_next_line(0, &str);
	free(str);
	while (index < y)
	{
		get_next_line(0, &str);
		playing_field[index] =  ft_strcpy(playing_field[index], str + 4);
		free(str);
		index++;
	}
	create_heat_map();
	init_heat_map();
	put_index();
}

void	start_pos()
{
	un_int i;
	static un_int j;

	if (j == map_size_y)
		return ;
	j = 0;
	while (++j < map_size_y)
	{
		i = 0;
		while (++i < map_size_x)
		{
			if ((playing_field[j][i] == player_my[0])
					|| (playing_field[j][i] == player_my[1]))
			{
				start_my_x = i;
				start_my_y = j;
			}
			if((playing_field[j][i] == player_en[0])
					|| (playing_field[j][i] == player_en[1]))
			{
				start_enemy_x = i;
				start_enemy_y = j;
			}
		}
	}
}

int		mem_alloc_card(const char *str)
{
	char			*size_map;
	VERTICAL		y;
	HORIZONTAL		x;
	un_int			index;
	
	index = 0;
	size_map = (char *)str + (LEN_MAPS + 1);
	y = ft_atoi(size_map);
	size_map += ft_lennumb(y) + 1;
	x = ft_atoi(size_map);
	playing_field = (char **)malloc((y + 1) * (sizeof(char *)));
	playing_field[y] = NULL;
	while (index < y)
	{
		playing_field[index] = (char *)malloc((x + 1) * (sizeof(char)));
		index++;
	}
	map_size_x = x;
	map_size_y = y;
	ft_record_map(y);
	start_pos();
	return (SUCSES);
}

void	real_pos_figures(void)
{
	un_int	index;
	un_int	jindex;

	g_piece.start_x = g_piece.size_x;
	g_piece.start_y = g_piece.size_x;
	index = 0;
	while (index < g_piece.size_y)
	{
		jindex = 0;
		while (jindex < g_piece.size_x)
		{
			if (figures_field[index][jindex] == '*')
			{
				if (jindex < g_piece.start_x)
					g_piece.start_x = jindex;
				if (jindex > g_piece.end_x)
					g_piece.end_x = jindex;
				if (index < g_piece.start_y)
					g_piece.start_y = index;
				if (index > g_piece.end_y)
					g_piece.end_y = index;
			}
			jindex++;
		}
		index++;
	}
	g_piece.real_x = (g_piece.end_x - g_piece.start_x) + 1;
	g_piece.real_y = (g_piece.end_y - g_piece.start_y) + 1;
}

void	ft_record_figures(VERTICAL y)
{
	char *str;
	int status_read;
	un_int index;

	str = NULL;
	status_read = 0;
	index = 0;
	while (index < y)
	{
		get_next_line(0, &str);
		figures_field[index] = ft_strcpy(figures_field[index], str);
		index++;
		free(str);
	}
	real_pos_figures();
}

void	mem_alloc_figures(const char *str)
{
	char			*size_map;
	VERTICAL		y;
	HORIZONTAL		x;
	un_int			index;

	index = 0;
	size_map = (char *)str + (LEN_FIGURES + 1);
	y = ft_atoi(size_map);
	size_map += ft_lennumb(y) + 1;
	x = ft_atoi(size_map);
	figures_field = (char **)malloc((y + 1) * (sizeof(char *)));
	figures_field[y] = NULL;
	while (index < y)
	{
		figures_field[index] = (char *)malloc((x + 1) * (sizeof(char)));
		index++;
	}
	ft_record_figures(y);
	g_piece.size_x = x;
	g_piece.size_y = y;
	return ;
}

int        last_try()
{
    int    i;
    int    i2;
    int    ret;
    
    i = -1;
    g_piece.final_x = 0;
    g_piece.final_y = 0;
    ret = 0;
    while (++i < (int)map_size_y - 1)
    {
        i2 = -1;
        while (++i2 < (int)map_size_x - 1)
        {
            ret = placable(i, i2);
            if (ret == 0)
            {
                ft_printf ("%d %d\n",g_piece.final_y, g_piece.final_x);
                return (0);
            }
        }
    }
    return (1);
}
char	**ft_read_map(void)
{
	char	*map;
	int		status_read;

	map = NULL;
	while (1)
	{
		get_next_line(0, &map);
		if (ft_strncmp(map, PLAYER, LEN_PLAYER) == 0)
		{
			ft_identify_player(map);
		}
		else if (ft_strncmp(map, MAPS, LEN_MAPS) == 0)
		{
			mem_alloc_card(map);
		}
		else if (ft_strncmp(map, FIGURES, LEN_FIGURES) == 0)
		{
			mem_alloc_figures(map);
			if (finding_place_for_figure() == 1)
			{
				if (last_try() == 1)
				{
					ft_printf ("%d %d\n", g_piece.final_y, g_piece.final_x);
					exit (1);
				}
			}
		}
			// free(map);
			// map = NULL;
		}
	// ft_printf ("player = {%s}\n", player_my);
	// for (int i = 0; playing_field[i]; i++)
	// 	ft_printf ("%s\n", playing_field[i]);
	// for (int i = 0; figures_field[i]; i++)
	// 	ft_printf ("%s\n",figures_field[i]);
	ft_free();
	return (NULL);
}
