#include "../includes/filler.h"


char	player = '!';

void	ft_identify_player(const char *str)
{
	char			*str_name;
/*
**  $$$ exec p2
**  01234567890
*/ 
	if (ft_strstr(str, NAME_PLAYER) == NULL)
	{
//		ft_printf ("NOT NAME!!\n"); // debug
		return ;
	}
	else
	{
		str_name = ((char *)str + (LEN_PLAYER + 2));
		if (str_name[0] == '1')
		{
			player = 'O';
		}
		else if (str_name[0] == '2')
		{
			player = 'X';
		}
	}
}