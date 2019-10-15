#include "../includes/filler.h"

char	*player_my = NULL;
char	*player_en = NULL;
char	play_one[] = "Oo";
char	play_two[] = "Xx";
extern char			**playing_field;
extern VERTICAL		map_size_y;
extern HORIZONTAL	map_size_x;
extern  FILE *g_fd;

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

void	size_map(char *str)
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
}

void	name_game(char *str)
{
	char *str_name;

	str_name = NULL;
		
	str_name = str + 10;
	if (str_name[0] == '1')
	{
		player_my = play_one;
		player_en = play_two;
	}
	else if(str_name[0] == '2')
	{
		player_my = play_two;
		player_en = play_one;
	}
}

int	ft_identify_player(char *str)
{
	char			*str_name;
	int				s_read;
/*
**  $$$ exec p2
**  01234567890
*/ 
	if (!(str = ft_strnew(1024)))
		return (0);
	while (get_next_line(0, &str) > 0)
	{
		if (ft_strstr(str, PLAYER) != NULL && ft_strstr(str, NAME_PLAYER) != NULL)
			name_game(str);
		if (ft_strstr(str, MAPS) != NULL)
		{
			size_map(str);
			return (1) ;
		}
	}
	return (0);
}
