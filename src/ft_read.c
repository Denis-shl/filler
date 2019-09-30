
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
}

void	start_pos()
{
	un_int i;
	static un_int j;
	printf ("j = {%d}\n", map_size_y);

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
	printf ("x_my = {%d} x_en = {%d} y_my = {%d} y_en = {%d}\n",start_my_x, start_enemy_x, start_my_y, start_enemy_y);
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
	ft_record_map(y);
	map_size_x = x;
	map_size_y = y;
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
	while ((status_read = get_next_line(0, &str)) && (index < y))
	{
		if (status_read == 0)
		{
			ft_printf ("ERROR read gnl!!\n{ft_record_figures}\n"); // fix 
			return ;
		}
		figures_field[index] = ft_strcpy(figures_field[index], str);
		// ft_printf ("%s\n", figures_field[index]);
		index++;
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
	x =  ft_atoi(size_map);
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
                ft_printf ("%d %d\n",g_piece.final_x, g_piece.final_y);
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
					ft_printf ("%d %d\n", g_piece.final_x, g_piece.final_y);
					exit (1);
				}
			}
		}
			free(map);
		}
	// ft_printf ("player = {%s}\n", player_my);
	// for (int i = 0; playing_field[i]; i++)
	// 	ft_printf ("%s\n", playing_field[i]);
	// for (int i = 0; figures_field[i]; i++)
	// 	ft_printf ("%s\n",figures_field[i]);
	ft_free();
	return (NULL);
}
