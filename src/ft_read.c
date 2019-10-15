
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
			return (-1) ;

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
	free(str);
	return (0);
}


void		ft_del()
{
	int index;
	int jindex;

	index = 0;
	jindex = 0;
	while (index < map_size_y)
	{
		free(heat_map[index]);
	}
	free(heat_map);
	heat_map = NULL;
}

void		ft_read_map(void)
{
	char	*map;
	int		status_read;
	int index = 0;

	map = NULL;
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
			create_heat_map();
			init_heat_map();
			put_index();
			finding_place_for_figure();
			ft_putnbr(g_piece.tmp_y);
			ft_putchar(' ');
			ft_putnbr(g_piece.tmp_x);
			ft_putchar('\n');
		}
		else
		{
			return ;
		}
	}
	ft_free();
}
