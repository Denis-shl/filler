
#include "../includes/filler.h"

char		**playing_field = NULL;
extern char	player;

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

int		mem_alloc_card(const char *str)
{
	char			*size_map;
	VERTICAL		y;
	HORIZONTAL		x;
	/*
	 * Plateau 15 17
	 * 0123456789012
	*/
	size_map = (char *)str + (LEN_MAPS + 1);
	y = ft_atoi(size_map);
	size_map += ft_lennumb(y) + 1;
	x = ft_atoi(size_map);
	playing_field = (char **)malloc((y + 1) * (sizeof(char *)));
	playing_field[y] = NULL;
	while (--y)
	{
		playing_field[y] = (char *)malloc((x + 1) * (sizeof(char)));
	}
	return (SUCSES);

}

char	**ft_read_map(void)
{
	char	*map;
	int		status_read;

	while ((status_read = get_next_line(0, &map)))
	{
		if (ft_strncmp(map, PLAYER, LEN_PLAYER) == 0)
		{
			ft_identify_player(map);
		}
		if (ft_strncmp(map, MAPS, LEN_MAPS) == 0)
		{
			mem_alloc_card(map);
			break;
		}
		else if (ft_strncmp(map, FIGURES, LEN_FIGURES) == 0)
		{
			;
		}
		else
		{
			;// error
		}
		free(map);
	}
	free(map);
	ft_free();
	printf ("%c\n", player);
	return (NULL);
}
