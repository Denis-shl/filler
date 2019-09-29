
#include "../includes/filler.h"

char		**playing_field = NULL;
char		**figures_field = NULL;
extern char	player;
VERTICAL	map_size_y;
HORIZONTAL	map_size_x;

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
//	ft_printf ("x = {%d}\n",  y);
	str = NULL;
	index = 0;
//	ft_printf ("DEBUG ft_record_map!!\n"); // debug
	while ((status_read = get_next_line(0, &str)) && (index < y))
	{
		if (status_read == 0)
		{
			ft_printf ("ERROR read gnl!!\n{ft_record_map}\n");
		}
		playing_field[index] =  ft_strcpy(playing_field[index], str);
		index++;
	}
}

int		mem_alloc_card(const char *str)
{
	char			*size_map;
	VERTICAL		y;
	HORIZONTAL		x;
	un_int			index;
	/*
	 * Plateau 15 17
	 * 0123456789012
	*/
	index = 0;
	size_map = (char *)str + (LEN_MAPS + 1);
	y = ft_atoi(size_map);
	size_map += ft_lennumb(y) + 1;
	x = ft_atoi(size_map);
//	ft_printf ("x = {%d}\ny = {%d}\n",x, y);
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
	return (SUCSES);
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
			ft_printf ("ERROR read gnl!!\n{ft_record_figures}\n");
			return ;
		}
		figures_field[index] = ft_strcpy(figures_field[index], str);
		index++;
	}
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
//	ft_printf ("x = {%d}\n y = {%d}\n", x ,y); // debug
	ft_record_figures(y);
	return ;
}
char	**ft_read_map(void)
{
	char	*map;
	int		status_read;

	map = NULL;
	while ((status_read = get_next_line(0, &map)))
	{
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
			finding_place_for_figure();
		}
		else if (status_read == -1)
		{
			ft_printf ("ERROR read gnl!!\n");
			free(map);
			return (NULL);// debug and fix
		}
		free(map);
	}
	ft_printf ("player = {%c}\n", player);
	for (int i = 0; playing_field[i]; i++)
		ft_printf ("%s\n", playing_field[i]);
	for (int i = 0; figures_field[i]; i++)
		ft_printf ("%s\n",figures_field[i]);
	ft_free();
	return (NULL);
}
