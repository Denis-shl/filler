
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


void		size_figr(char *str)
{
	char			*size_map;
	VERTICAL		y;
	HORIZONTAL		x;
	int				index;
	

	fprintf (g_fd, "debug mem alloc figures\n");
	fprintf (g_fd, "do str = %s\n", str);
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
	g_piece.size_x = x;
	g_piece.size_y = y;
}

int		map_and_figr()
{
	char *str;
	int index;
	int jindex;

	index = -1;
	jindex = -1;
	while (1)
	{
		str = ft_strnew(1024);
		read_str(str);
		if (str == NULL || str[0] == '\0' || str[0] == '\n')
			break ;
		// fprintf(stderr, "%s", str);
		if (str && str[0] == '0')
			ft_strcpy(playing_field[++jindex], str + 4);
		else if (str && ft_strstr(str, FIGURES) != NULL)
			size_figr(str);
		else if (str && (str[0] == '.' || str[0] == '*'))
		{
			ft_strcpy(figures_field[++index], str);
			if (index == g_piece.size_y - 1)
			{
				free(str);
				return(1) ;
			}
		}
	}
	fprintf(g_fd, "str = {%s}\n", str);
	free(str);
	return (0);
}

void		trace_fix()
{
	
	for (int i = 0; map_size_y > i; i++)
	{
		for(int j = 0; j < map_size_x; j++)
		{
			fprintf(g_fd, "%4d", heat_map[i][j]);
		}
		fprintf (g_fd, "\n");
	}
}

void		ft_read_map(void)
{
	char	*map;
	int		status_read;
	int index = 0;

	map = NULL;
	g_fd = fopen("debager", "w++");
	if (ft_identify_player(map) == 0)
	{
		free(map);
		return ;
	}
	free(map);
	while (1)
	{
		if (map_and_figr() == 1)
		{
			init_struct();
			create_heat_map();
			init_heat_map();
			put_index();
			trace_fix();
			finding_place_for_figure();
			fprintf (stderr, "{%d} {%d}\n", g_piece.tmp_x, g_piece.tmp_y);
			ft_putnbr(g_piece.tmp_y);
			ft_putchar(' ');
			ft_putnbr(g_piece.tmp_x);
			ft_putchar('\n');
			fprintf (g_fd, "result: x = {%d} y = {%d}\n", g_piece.tmp_x, g_piece.tmp_y);
		}
		else
		{
			fprintf (g_fd, "ERROR\n");
			continue ;
		}
	}
	fclose(g_fd);
	ft_free();
}
