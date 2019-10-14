
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
/* debug files*/
FILE *g_fd;

int gnl(int fd, char **line)
{
	int ret;
	char *tmp;
	char buf[2];

	if (!line)
		return (-1);
	*line = ft_strnew(0);
	ret = 0;
	ft_bzero(buf, 2);
	while ((read(fd, buf, 1) > 0) && buf[0] != '\n' && buf[0] != '\0')
	{
		ret++;
		tmp = ft_strjoin(*line, buf);
		free(*line);
		*line = tmp;
	}
	return (ret);
}

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
	// get_next_line(0, &str);
	gnl(0, &str);
	while (index < y)
	{
		// get_next_line(0, &str);
		gnl(0, &str);
		playing_field[index] = ft_strcpy(playing_field[index], str + 4);
		fprintf (g_fd, "%s\n", str);
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

int		mem_alloc_card(char *str)
{
	char			*size_map;
	VERTICAL		y;
	HORIZONTAL		x;
	un_int			index;

	fprintf (g_fd, "mem alloc card = {%s}\n", str);
	index = 0;
	if (str[0] == '\0')
		gnl(0, &str);
	if (ft_strstr(str, MAPS) == NULL)
		return (0);
	size_map = (char *)str + (LEN_MAPS + 1);
	y = ft_atoi(size_map);
	size_map += ft_lennumb(y) + 1;
	x = ft_atoi(size_map);
	fprintf (g_fd, "x = {%d}, y = {%d}\n", x, y);
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
	/* debug info*/
	fprintf (g_fd, "map\n");
	for (int i = 0; playing_field[i]; i++)
		fprintf (g_fd, "%2d %s\n",i, playing_field[i]);
	fprintf (g_fd, "heat map\n");
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			fprintf (g_fd, "%d", heat_map[i][j]);
		}
		fprintf (g_fd, "\n");
	}

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

void	append_str(char *str, char *buff)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	str[i] = buff[0];
}

int		read_str(char *str)
{
	char	buff[1];

	while (1)
	{
		read(0, buff, 1);
		if (buff[0] == '\0')
			return (-1);
		append_str(str, buff);
		if (buff[0] == '\n')
			return (0);
	}
}

int		ft_record_figures(VERTICAL y, HORIZONTAL x)
{
	char	*str;
	int		status_read;
	int		index;
	int		jindex;
	char *buf;

	str = NULL;
	status_read = 0;
	index = 0;
	fprintf (g_fd, "ft record figures\n y = %d\n", y);
	fprintf (g_fd, "ft record figures\n x = %d\n", x);
	while (index < y)
	{
		// if ((status_read = get_next_line(0, &str)) != 1)
		// 	return (0);
		str = ft_strnew(x + 1);
		// if (gnl(0, &str) == -1)
		// 	fprintf(g_fd, "ERROR READ\n");
		if (index == y - 1)
			read(0, str, x);
		else
		{
				read(0, str, x);
		}
		
		fprintf (g_fd, "index = %d\nread = %s\n", index, str);
		str[x] = '\0';
		figures_field[index] = ft_strcpy(figures_field[index], str);
		index++;
		free(str);
	}
	// real_pos_figures();
	return(1);
}

int		mem_alloc_figures(char *str)
{
	char			*size_map;
	VERTICAL		y;
	HORIZONTAL		x;
	int				index;
	

	fprintf (g_fd, "DEBUG mem alloc figures\n");
	fprintf (g_fd, "do str = %s\n", str);
	if (get_next_line(0, &str) != 1  || ft_strstr(str, FIGURES) == NULL)
	{
		fprintf (g_fd, "FIGURE ERROR = %s\n", str);
		return (0);
	}
	fprintf (g_fd, "FIGUre   str = %s\n", str);
	index = 0;
	size_map = (char *)str + (LEN_FIGURES + 1);
	y = ft_atoi(size_map);
	size_map += ft_lennumb(y) + 1;
	x = ft_atoi(size_map);
	figures_field = (char **)malloc((y + 1) * (sizeof(char *)));
	figures_field[y] = NULL;
	free(str);
	while (index < y)
	{
		figures_field[index] = (char *)malloc((x + 1) * (sizeof(char)));
		index++;
	}
	if (ft_record_figures(y, x) == 0)
		return (0);
	g_piece.size_x = x;
	g_piece.size_y = y;

	fprintf (g_fd, "figures field\n");
	for (int i = 0; figures_field[i]; i++)
		fprintf (g_fd, "%s\n", figures_field[i]);
	return (1);
}

void	init_struct()
{
	g_piece.real_x = 0;
	g_piece.bl_f = 0;
	g_piece.flag = 0;
	g_piece.real_y = 0;
	g_piece.size_x = 0;
	g_piece.size_y = 0;
	g_piece.start_x = 0;
	g_piece.start_y = 0;
	g_piece.end_x = 0;
	g_piece.end_y = 0;
	g_piece.final_x = 0;
	g_piece.final_y = 0;
	g_piece.tmp_x = 0;
	g_piece.tmp_y = 0;
	g_piece.nbr_contact = 0;
	g_piece.score = 0;
	g_piece.score2 = 0;
	g_piece.tmp_x2 = 0;
	g_piece.tmp_y2 = 0;
	g_piece.x = 0;
	g_piece.y = 0;
	g_piece.tempj = 0;
	g_piece.tempi = 0;
	g_piece.i = -1;
	g_piece.j = 0;
}

void		ft_read_map(void)
{
	char	*map;
	int		status_read;

	init_struct();
	map = NULL;
	g_fd = fopen("debager", "w++");
	if (ft_identify_player(map) == 0)
		return ;
	while (1)
	{
		if (mem_alloc_card() == 0)
			return ;
		if (mem_alloc_figures() == 0)
			return ;
		finding_place_for_figure();
		printf("%d %d\n", g_piece.tmp_y, g_piece.tmp_x);
		ft_free();
		init_struct();
		free(map);
	}
	fclose(g_fd);
	ft_free();
}
