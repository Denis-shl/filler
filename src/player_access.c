#include "../includes/filler.h"

char	*player_my = NULL;
char	*player_en = NULL;
char	play_one[] = "Oo";
char	play_two[] = "Xx";

void	ft_identify_player(const char *str)
{
	char			*str_name;
/*
**  $$$ exec p2
**  01234567890
*/ 
	if (ft_strstr(str, NAME_PLAYER) == NULL)
	{
		return ;
	}
	else
	{
		str_name = ((char *)str + (LEN_PLAYER + 2));
		if (str_name[0] == '1')
		{
			player_my = play_one;
			player_en = play_two;

		}
		else if (str_name[0] == '2')
		{
			player_my = play_two;
			player_en = play_one;
		}
	}
}
